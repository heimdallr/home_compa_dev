#include <atomic>
#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

#include <QString>

#include "log.h"

#include "GeneratorHandler.h"
#include "ResultSaver.h"

namespace HomeCompa { namespace sl {

class ResultSaver::Impl
{
	std::condition_variable m_condition;
	std::mutex m_queueGuard;
	std::queue<Data> m_queue;
	std::promise<void> m_promice;
	std::atomic_bool m_running{ true };
	GeneratorHandler &m_handler;
	std::ofstream m_outp;
	std::thread m_thread;

public:
	Impl(GeneratorHandler &handler, const QString &fileName)
		: m_handler(handler)
		, m_outp(fileName.toStdString())
		, m_thread(&Impl::ThreadFunction, this)
	{
		if (!m_outp.is_open())
			throw std::invalid_argument("Cannot write to " + fileName.toStdString());

		auto threadStartWaiter = m_promice.get_future();
		threadStartWaiter.get();
	}
	~Impl()
	{
		log() << "saver going dead" << std::endl;
		{
			std::unique_lock<std::mutex> lock(m_queueGuard);
			std::queue<Data>().swap(m_queue);
		}
		Stop();
		if (m_thread.joinable())
			m_thread.join();

		log() << "saver dead" << std::endl;
	}
	void Save(Data &&data)
	{
		log() << "to save: " << data.size() << std::endl;

		std::unique_lock<std::mutex> lock(m_queueGuard);
		m_queue.emplace();
		m_queue.back().swap(data);
		m_condition.notify_all();
	}
	void Stop()
	{
		m_running = false;
		std::unique_lock<std::mutex> lock(m_queueGuard);
		m_condition.notify_all();
	}
private:
	void ThreadFunction()
	{
		m_promice.set_value();
		while (true)
		{
			Data data;
			{
				std::unique_lock<std::mutex> lock(m_queueGuard);
				m_condition.wait(lock, [this]()
				{
					return !m_running || !m_queue.empty();
				});
				if (!m_running && m_queue.empty())
					break;

				if (!m_queue.empty())
				{
					m_queue.front().swap(data);
					m_queue.pop();
				}
			}
			log() << "saving: " << data.size() << std::endl;
			for (const auto &d : data)
				Out(m_outp, d);

			m_handler.Saved(data.size());
		}

		m_handler.SaveReady();
	}
};

ResultSaver::ResultSaver(GeneratorHandler &handler, const QString &fileName)
	: m_impl(std::make_unique<Impl>(handler, fileName))
{
}

ResultSaver::~ResultSaver() = default;

void ResultSaver::Save(Data &&data)
{
	m_impl->Save(std::forward<Data>(data));
}

void ResultSaver::Stop()
{
	m_impl->Stop();
}

} }
