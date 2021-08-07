#pragma once
#include <queue>
#include <mutex>
#include <pthread.h>

// ��������ṹ��
using callback = void(*)(void*);
template <typename T>
struct Task
{
    Task<T>()
    {
        function = nullptr;
        arg = nullptr;
    }
    Task<T>(callback f, void* arg)
    {
        function = f;
        this->arg = (T*)arg;
    }
    callback function;
    T* arg;
};

// �������
template <typename T>
class TaskQueue
{
public:
    TaskQueue();
    ~TaskQueue();

    // �������
    void addTask(Task<T>& task);
    void addTask(callback func, void* arg);

    // ȡ��һ������
    Task<T> takeTask();

    // ��ȡ��ǰ�������������
    inline int taskNumber()
    {
        return m_queue.size();
    }

private:
    pthread_mutex_t m_mutex;    // ������
    std::queue<Task<T>> m_queue;   // �������
};

