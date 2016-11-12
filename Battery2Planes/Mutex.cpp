#include "Mutex.h"
Mutex::Mutex(void)
{
    InitializeCriticalSection(&m_criticalSection);
}
Mutex::~Mutex(void)
{
    DeleteCriticalSection(&m_criticalSection);//��֤��������ʱ���ܹ�ɾ���ٽ���
}
void Mutex::Lock()
{
    EnterCriticalSection(&m_criticalSection);
}
void Mutex::UnLock()
{
    LeaveCriticalSection(&m_criticalSection);
}
