#pragma once
#include <vector>
#include <array>
#include <unordered_map>
#include "..\Graphics\GUI\Event.h"
#include <glm\glm.hpp>

#define MAX_POSITION_COMPONENTS		64
#define MAX_VELOCITY_COMPONENTS		64
#define MAX_SPRITE_COMPONENTS		64
#define MAX_HEALTH_COMPONENTS		64

#define EXTRA_BUFFER_STORAGE_SIZE	10

namespace garm {
	namespace graphics {

		enum class ComponentTypeBit : uint64_t {
			COMPONENT_TYPE_POSITION = 0x00000001,
			COMPONENT_TYPE_VELOCITY = 0x00000002,
			COMPONENT_TYPE_SPRITE = 0x00000004,
			COMPONENT_TYPE_HEALTH = 0x00000008,
		};

		class Entity{
			static uint32_t IDGenerator;
			uint32_t ID;
			uint64_t componentKey;
		public:
			Entity() { ID = IDGenerator++; }
			
		public:
			//bool operator ==(const Entity& other) { return (ID == other.ID) && (componentKey == other.componentKey); }
		public:
			uint32_t getId() const { return ID; }
			uint64_t getComponentKey() const { return componentKey; }
			bool AddComponent(ComponentTypeBit component) {
				if ((componentKey & (uint64_t)component) == (uint64_t)component)
					return false;
				componentKey |= (uint64_t)component;
				return true;
			}
			bool RemoveComponent(ComponentTypeBit component){
				if ((componentKey & (uint64_t)component) != (uint64_t)component)
					return false;
				componentKey -= (uint64_t)component;
				return true;
			}
		};
		bool operator ==(const Entity& e1, const Entity& e2);

		struct EntityHasher {
			size_t operator()(const Entity& e) const { return (size_t)e.getId(); }
		};

		struct Instance { unsigned int i; };		

		class TransformComponentManager {
			struct InstanceData {
				unsigned int numInstances = 0;
				unsigned int numAllocatedInstances = 0;
				void* buffer;

				Entity* entity;
				glm::mat4* local;
				glm::mat4* world;
				Instance* parent;
				Instance* firstChild;
				Instance* nextSibling;
				Instance* prevSibling;
			};
			InstanceData data;
			std::unordered_map<Entity, unsigned int, EntityHasher> map;

			Instance MakeInstance(unsigned int i) { Instance instance = { i }; return instance; }
			Instance Lookup(Entity entity) { return MakeInstance(map.at(entity)); }

			glm::mat4 Local(Instance instance) { return data.local[instance.i]; }
			glm::mat4 World(Instance instance) { return data.world[instance.i]; }
			Instance Parent(Instance instance) { return data.parent[instance.i]; }
			Instance FirstChild(Instance instance) { return data.firstChild[instance.i]; }
			Instance NextSibling(Instance instance) { return data.nextSibling[instance.i]; }
			Instance PrevSibling(Instance instance) { return data.prevSibling[instance.i]; }

			void SetLocal(Instance instance, const glm::mat4& local) { data.local[instance.i] = local; }
			void SetWorld(Instance instance, const glm::mat4& local) { data.world[instance.i] = local; }
			void SetParent(Instance instance, Instance parent) { data.parent[instance.i] = parent; }
			void SetFirstChild(Instance instance, Instance firstChild) { data.firstChild[instance.i] = firstChild; }
			void SetNextSibling(Instance instance, Instance nextSibling) { data.nextSibling[instance.i] = nextSibling; }
			void SetPrevSibling(Instance instance, Instance prevSibling) { data.prevSibling[instance.i] = prevSibling; }
			
			void Allocate(unsigned int size) {
				assert(size > data.numAllocatedInstances);
				InstanceData newData;
				newData.numInstances = data.numInstances;
				newData.numAllocatedInstances = size;
				newData.buffer = new int8_t[sizeof(Entity) + 2 * sizeof(glm::mat4) + 4 * sizeof(Instance)];
				newData.entity = (Entity*)newData.buffer;
				newData.local = (glm::mat4*)(newData.entity + size);
				newData.world = newData.local + size;
				newData.parent = (Instance*)(newData.world + size);
				newData.firstChild = newData.parent + size;
				newData.nextSibling = newData.firstChild + size;
				newData.prevSibling = newData.nextSibling + size;

				memcpy(newData.entity, data.entity, data.numInstances * sizeof(Entity));
				memcpy(newData.local, data.local, data.numInstances * sizeof(glm::mat4));
				memcpy(newData.world, data.world, data.numInstances * sizeof(glm::mat4));
				memcpy(newData.parent, data.parent, data.numInstances * sizeof(Instance));
				memcpy(newData.firstChild, data.firstChild, data.numInstances * sizeof(Instance));
				memcpy(newData.nextSibling, data.nextSibling, data.numInstances * sizeof(Instance));
				memcpy(newData.prevSibling, data.prevSibling, data.numInstances * sizeof(Instance));
			}

			void Destroy(unsigned int i) {
				unsigned int last = data.numInstances - 1;
				Entity e = data.entity[i];
				Entity lastEntity = data.entity[last];

				data.entity[i]		= data.entity[last];
				data.local[i]		= data.local[last];
				data.world[i]		= data.world[last];
				data.parent[i]		= data.parent[last];
				data.firstChild[i]	= data.firstChild[last];
				data.nextSibling[i] = data.nextSibling[last];
				data.prevSibling[i] = data.prevSibling[last];

				map[lastEntity] = i;
				map.erase(e);
			}
		};

		class MotionComponentManager {
			struct InstanceData {
				unsigned int numInstances = 0;
				unsigned int numAllocatedInstances = 0;
				void* buffer = nullptr;

				Entity* entity;
				glm::vec3* position;
				glm::vec3* velocity;
				glm::vec3* acceleration;
			};
			InstanceData data;
			std::unordered_map<Entity, unsigned int, EntityHasher> map;

			Instance MakeInstance(unsigned int i) { Instance instance = { i }; return instance; }
			Instance Lookup(Entity entity) { return MakeInstance(map.at(entity)); }
			void AddComponents(	const std::vector<Entity>& entities,
					const std::vector<glm::vec3>& pos,
					const std::vector<glm::vec3>& vel,
					const std::vector<glm::vec3>& acc) {
				assert((entities.size() == pos.size()) && (vel.size() == acc.size()) && (pos.size() == vel.size()));
				
				if (data.numAllocatedInstances < data.numInstances + entities.size()) {
					Allocate(data.numInstances + entities.size() + EXTRA_BUFFER_STORAGE_SIZE);
				}
				for (unsigned i = 0; i < entities.size(); i++)
					data.entity[data.numInstances] = entities[i];
				for (unsigned i = 0; i < entities.size(); i++)
					data.position[data.numInstances] = pos[i];
				for (unsigned i = 0; i < entities.size(); i++)
					data.velocity[data.numInstances] = vel[i];
				for (unsigned i = 0; i < entities.size(); i++)
					data.acceleration[data.numInstances] = acc[i];
			}
			void AddComponent(Entity entity, const glm::vec3& pos, const glm::vec3& vel, const glm::vec3& acc) {
				if (data.numAllocatedInstances == data.numInstances) {
					Allocate(data.numAllocatedInstances + EXTRA_BUFFER_STORAGE_SIZE);
				}
				data.entity[data.numInstances] = entity;
				data.position[data.numInstances] = pos;
				data.velocity[data.numInstances] = vel;
				data.acceleration[data.numInstances] = acc;
				map[entity] = data.numInstances;
				data.numInstances++;
			}
			void AddComponent(Entity entity) {
				if (data.numAllocatedInstances == data.numInstances) {
					Allocate(data.numAllocatedInstances + EXTRA_BUFFER_STORAGE_SIZE);
				}
				data.entity[data.numInstances] = entity;
				data.position[data.numInstances] = glm::vec3();
				data.velocity[data.numInstances] = glm::vec3();
				data.acceleration[data.numInstances] = glm::vec3();
				map[entity] = data.numInstances;
				data.numInstances++;
			}

			glm::vec3 Position(Instance instance) { return data.position[instance.i]; }
			glm::vec3 Velocity(Instance instance) { return data.position[instance.i]; }
			glm::vec3 Acceleration(Instance instance) { return data.position[instance.i]; }

			void SetPosition(Instance instance, const glm::vec3& pos) { data.position[instance.i] = pos; }
			void SetVelocity(Instance instance, const glm::vec3& vel) { data.velocity[instance.i] = vel; }
			void SetAcceleration(Instance instance, const glm::vec3& acc) { data.acceleration[instance.i] = acc; }

			void Allocate(unsigned int size) {
				assert(size > data.numAllocatedInstances);
				InstanceData newData;
				newData.numInstances = data.numInstances;
				newData.numAllocatedInstances = size;
				newData.buffer = new int8_t[sizeof(Entity) + 3 * sizeof(glm::vec3)];
				newData.entity = (Entity*)(newData.buffer);
				newData.position = (glm::vec3*)(newData.entity + size);
				newData.velocity = (glm::vec3*)(newData.position + size);
				newData.acceleration = (glm::vec3*)(newData.velocity + size);

				memcpy(newData.entity, data.entity, data.numInstances * sizeof(Entity));
				memcpy(newData.position, data.position, data.numInstances * sizeof(glm::vec3));
				memcpy(newData.velocity, data.velocity, data.numInstances * sizeof(glm::vec3));
				memcpy(newData.acceleration, data.acceleration, data.numInstances * sizeof(glm::vec3));

				delete[] data.buffer;
				data = newData;
			}

			void Destroy(unsigned int i) {
				unsigned last		= data.numInstances - 1;
				Entity e			= data.entity[i];
				Entity lastEntity	= data.entity[last];

				data.entity[i]			= data.entity[last];
				data.position[i]		= data.position[last];
				data.velocity[i]		= data.velocity[last];
				data.acceleration[i]	= data.acceleration[last];

				map[lastEntity] = i;
				map.erase(e);
			}
			
		};

		class RenderableComponentManager {
			struct InstanceData {
				unsigned int numInstances = 0;
				unsigned int numAllocatedInstances = 0;
				void* buffer = nullptr;

				Entity* entity;
				bool* owned;
			};
			InstanceData data;
			std::unordered_map<Entity, unsigned int, EntityHasher> map;

			Instance MakeInstance(unsigned int i) { Instance instance = { i }; return instance; }
			Instance Lookup(Entity entity) { return MakeInstance(map.at(entity)); }
		};

		class RenderableResourceComponentManager {
			struct InstanceData {
				unsigned int numInstances = 0;
				unsigned int numAllocatedInstances = 0;
				void* buffer = nullptr;



			};
			InstanceData data;
			std::unordered_map<Entity, unsigned int, EntityHasher> map;

			Instance MakeInstance(unsigned int i) { Instance instance = { i }; return instance; }
			Instance Lookup(Entity entity) { return MakeInstance(map.at(entity)); }
		};

		class System{
			
		};

		class EntityManager {
			std::vector<Entity> entities;
			std::unordered_map<Entity, unsigned int, EntityHasher> map;	//seems a bit pointless but might be usefull, for "dirty" flag sorting the array
		public:
			void MakeEntities(unsigned int num) { entities.resize(entities.size() + num); }
			void DeleteEntity(Entity entity);
		};

		class Camera {

		};

		class World {
			MotionComponentManager* motionComponentManager = nullptr;
			TransformComponentManager* transformComponentManager = nullptr;
			Camera* camera;
		public:
		};



		/////////////////////////////////////////
		//class Entity;
		//class Renderable;
		//
		//class EntityListener {
		//public:
		//	typedef Entity notifier_type;
		//	virtual bool AddRenderable(Entity* src, Renderable* renderable) { return true; }
		//
		//};
		//
		//class Component {
		//	Entity* owner;
		//public:
		//	virtual void Get() {}	//test
		//};
		//
		//class Renderable : Component {
		//	bool render = false;
		//public:
		//	inline bool shouldRender() const { return render; }
		//};
		//
		//class Renderer {
		//public:
		//	Renderer(){}
		//	void Render(const Renderable* renderable) {
		//
		//	}
		//};
		//
		//class Controller : Component {
		//
		//public:
		//	void Move();
		//};
		//
		//class Physics : Component {
		//
		//};
		//
		//class Entity : public event::Notifier<EntityListener> {
		//	std::vector<Component*> components;
		//	Entity();
		//	friend class Scene;
		//public:
		//	Entity(const Entity&) = default;
		//	void AddComponent(Component* component) {
		//		Renderable*  renderable;
		//		if ((renderable = dynamic_cast<Renderable*>(component)) != nullptr)
		//			Notify(&EntityListener::AddRenderable, renderable);
		//		components.push_back(component);
		//	}
		//};
		//
		//class Scene : public event::Listener<EntityListener> {
		//	std::vector<Entity*> entities;
		//	std::vector<Renderable*> renderables;
		//	Renderer renderer;
		//	virtual bool AddRenderable(Entity* src, Renderable* renderable) override {
		//		return true;
		//	}
		//public:
		//
		//	Entity* MakeEntity() {
		//		Entity* entity = new Entity();
		//		AttachTo(entity);
		//		entities.push_back(entity);
		//		return entity;
		//	}
		//
		//
		//	void Render() {
		//		for (const Renderable* renderable : renderables) {
		//			if(renderable->shouldRender())
		//				renderer.Render(renderable);
		//		}
		//	}
		//};

	}
}