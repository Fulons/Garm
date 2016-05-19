#pragma once
#include <vector>
#include <algorithm>

namespace garm { namespace event{

	template<class interface_type>
	class AbstractEvent {
	public:
		virtual bool operator()(interface_type* listener) const = 0;
	};

	class def_type { public: def_type() {} };
	template <typename T> struct arg_count { enum { count = 1 }; };
	template <> struct arg_count<def_type> { enum { count = 0 }; };
	template <unsigned> class num_type{};

	template<class interface_type, typename listener_func, typename p1_type = def_type, typename p2_type = def_type>
	class Event : public AbstractEvent<interface_type> {
	public:
		explicit Event(listener_func func, const p1_type& p1 = p1_type(), const p2_type& p2 = p2_type())
			: func(func), p1(p1), p2(p2) {}
		virtual bool operator()(interface_type* listener) const {
			const unsigned argCount = arg_count<p1_type>::count + arg_count<p2_type>::count;
			if (listener) return invokeImpl(listener, num_type<argCount>());
			return true;
		}
	protected:		
		template<class T> bool invokeImpl(T* listener, num_type<0>) const { return (bool)(listener->*func)(); }
		template<class T> bool invokeImpl(T* listener, num_type<1>) const { return (bool)(listener->*func)(p1); }
		template<class T> bool invokeImpl(T* listener, num_type<2>) const { return (bool)(listener->*func)(p1, p2); }
	private:
		const listener_func func;
		const p1_type p1;
		const p2_type p2;
	};

	template<class interface_type> class Listener;

	template<class interface_type>
	class Notifier {
	public:
		typedef Listener<interface_type> listener_type;
		friend class listener_type;
	private:
		std::vector<listener_type*> m_listeners;
	protected:
		Notifier(){}
		template<typename func_type>
		void Notify(func_type func) {
			typedef Event<interface_type, func_type, c_notifier_type*> event_type;
			DoEvent(event_type(func, static_cast<c_notifier_type*>(this)));
		}

		template<typename func_type, typename p1_type>
		void Notify(func_type func, const p1_type& p1) {
			typedef Event<interface_type, func_type, c_notifier_type*, p1_type> event_type;
			DoEvent(event_type(func, static_cast<c_notifier_type*>(this), p1));
		}

		template<typename func_type, typename p1_type, typename p2_type>
		void Notify(func_type func, const p1_type& p1, const p2_type& p2) {
			typedef Event<interface_type, func_type, c_notifier_type*, p1_type, p2_type> event_type;
			DoEvent(event_type(func, static_cast<c_notifier_type*>(this), p1, p2));
		}
		virtual ~Notifier(){
			for (size_t i = 0; i < m_listeners.size(); i++)
				m_listeners[i]->NotifierImpl_Deleted(static_cast<c_notifier_type*>(this));
		}
	private:
		bool Attach(listener_type* listener) {
			if (find(m_listeners.begin(), m_listeners.end(), listener) != m_listeners.end())
				return false;
			m_listeners.push_back(listener);
			return true;
		}
		bool Detach(listener_type* listener) {
			auto it = find(m_listeners.begin(), m_listeners.end(), listener);
			if (it == m_listeners.end())
				return false;
			m_listeners.erase(it);
			return true;
		}
		typedef Notifier<interface_type> self_type;
		typedef typename interface_type::notifier_type c_notifier_type;
		Notifier(const self_type&);
		self_type &operator=(const self_type&);
		void DoEvent(const AbstractEvent<interface_type>& event) {
			for (size_t i = 0; i < m_listeners.size(); i++)
				if (!event(m_listeners[i])) return;
		}
	};	

	template<class interface_type>
	class Listener : public interface_type {
	public:
		typedef Notifier<interface_type> notifier_type;
		typedef typename interface_type::notifier_type c_notifier_type;
		friend notifier_type;
	private:
		std::vector<notifier_type*> notifiers;
	public:
		void AttachTo(notifier_type* notifier) {
			if (notifier->Attach(this)) notifiers.push_back(notifier);
		}

		void DetachFrom(notifier_type* notifier) {
			auto it = find(notifiers.begin(), notifiers.end(), notifier);
			if (it != notifiers.end()) {
				notifiers.erase(it);
				notifier->Detach(this);
			}
		}
	protected:
		Listener(){}
		virtual ~Listener() {
			for (size_t i = 0; i < notifiers.size(); i++) notifiers[i]->Detach(this);
		}
		
		virtual void Notifier_Deleted(c_notifier_type* notifier){}
	private:
		virtual void NotifierImpl_Deleted(c_notifier_type* src){
			auto it = find(notifiers.begin(), notifiers.end(), static_cast<notifier_type*>(src));
			notifiers.erase(it);
			this->Notifier_Deleted(src);
		}
		typedef Listener<interface_type> self_type;
		Listener(const self_type&);
		self_type &operator=(const self_type&);
	};

} }