#pragma once
#include "cchannel.h"
#include <unordered_map>
#include <queue>
#include <memory>
#include <tuple>
#include <ctime>
#include <shared_mutex>

namespace fiber {
	class cchannel_simple : virtual public cchannel {
		static const inline std::string banner{ "SIMPLE-CHANNEL" };
	protected:
		virtual void OnGET(const cmsgid&& msg_id, const std::string&& path, const std::shared_ptr<fiber::crequest>& request);
		virtual void OnPOST(const cmsgid&& msg_id, const std::string&& path, const std::shared_ptr<fiber::crequest>& request);
		virtual void OnPUT(const cmsgid&& msg_id, const std::string&& path, const std::shared_ptr<fiber::crequest>& request);
		virtual void OnHEAD(const cmsgid&& msg_id, const std::string&& path, const std::shared_ptr<fiber::crequest>& request);
	public:
		using message = std::tuple<uint16_t, std::time_t, std::time_t, std::shared_ptr<fiber::crequest>, std::shared_ptr<fiber::crequest>>;

		cchannel_simple(const std::string& name, const core::coptions& options);
		virtual ~cchannel_simple();

		virtual void processing(const cmsgid& msg_id, const std::string& uri, const std::shared_ptr<fiber::crequest>& msg);
	private:
		std::string					queueName{};
		std::size_t					queueLimitCapacity{ 0 };
		std::string					queueDurability{};
		std::unordered_map<cmsgid, message>	msgPool;
		std::queue<cmsgid>		msgQueue;
		std::shared_mutex		msgSync;
	};
}