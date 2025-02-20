/*
 *	ipcs.h
 *
 * 
 *
 *
 *
 */

#pragma once
#include "Typedef.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>

#define KEY_NUM_SM		      1234          // 공유메모리 - 캡쳐 이미지
#define MEM_SIZE_SM	        512*4096      // 공유메모리 크기
// add. by ariari : 2022.11.09 : begin
#define KEY_NUM_SM2		      2234          // 공유메모리 - 캡쳐 이미지(lpr)
#define MEM_SIZE_SM2	      512*4096      // 공유메모리 크기
// add. by ariari : 2022.11.09 : end
#define KEY_NUM_SM_RES      1235          // 공유메모리 - 캡쳐 정보
#define MEM_SIZE_SM_RES	    32            // 공유메모리 크기
#define KEY_NUM_SM_LPR      1236          // 공유메모리 - 번호판 결과
#define MEM_SIZE_SM_LPR	    32            // 공유메모리 크기
// add. by ariari : 2021.12.08 - begin
#define KEY_NUM_SM_CAM      1237          // 공유메모리 - 카메라 파라미터
#define MEM_SIZE_SM_CAM	    256           // 공유메모리 크기
// add. by ariari : 2021.12.08 - end

#define KEY_NUM_MQ_GRAB     2345          // 메시지큐 - 캡쳐 정보(for preview)
#define KEY_NUM_MQ_GRAB_IMG 2346          // 메시지큐 - 이미지 캡쳐 상태(for lpr)
#define KEY_NUM_MQ_LPDR     3456          // 메시지큐 - LPDR
#define MQ_LPDR_MAX_QSIZE   100

//#define EN_LIST_DISP    // add. by ariari : 2022.07.19(for 도로공단 시험평가)
#ifdef EN_LIST_DISP
// add. by ariari : 2022.05.20 - begin
#define KEY_NUM_MQ_LPDR_INFO        4456          // 메시지큐 - LPDR_INFO(for preview)
#define MQ_LPDR_INFO_MAX_QSIZE      10            // 이미지내 번호판 검출 정보(다중검출)

#define KEY_NUM_SM_LPDR       3237          // 공유메모리 - 정보
#define MEM_SIZE_SM_LPDR	    1024           // 공유메모리 크기
// add. by ariari : 2022.05.20 - end

// add. by ariari : 2022.05.02 - begin
//#define EN_DEMO
#ifdef EN_DEMO
#define MQ_LPDR_MAX_QSIZE   1000
#endif
// add. by ariari : 2022.05.02 - end
#endif

class Ipcs
{
//////////////////////////////////////////////////////////////////////////////////////////////////////	
// Construction
//////////////////////////////////////////////////////////////////////////////////////////////////////	
public:
	Ipcs(int key, int size);
	virtual ~Ipcs();

//////////////////////////////////////////////////////////////////////////////////////////////////////	
// Attributes
//////////////////////////////////////////////////////////////////////////////////////////////////////	
public:

private:

protected:
  string 			msg;

  int   key_num;
  int   mem_size;
  bool  created;

//////////////////////////////////////////////////////////////////////////////////////////////////////	
// Operations
//////////////////////////////////////////////////////////////////////////////////////////////////////	

/////////////////////////////////////////////////////////////////////////////////////////////////////	
// Implementation
//////////////////////////////////////////////////////////////////////////////////////////////////////	

public:
  //////////////////////////////////////////////////////////////////////////////////////////////////////	
	// IPC : Shared Memory : 이미지 캡쳐
	//////////////////////////////////////////////////////////////////////////////////////////////////////
  int shmid;
	int SharedMemoryCreate();
  int SharedMemoryInit();
  int SharedMemoryRead(char *sMemory);
  int SharedMemoryWrite(char *shareddata, int size);
	int SharedMemoryFree(void);	
  //////////////////////////////////////////////////////////////////////////////////////////////////////	

  //////////////////////////////////////////////////////////////////////////////////////////////////////	
	// IPC : Message Queue
	//////////////////////////////////////////////////////////////////////////////////////////////////////
  int msqid;
	struct grab_data{
		int capWidth;
		int capHeight;
	};
	struct message_grab{
		long msg_type;
		struct grab_data data;
	};
	struct message_grab msq_grab;
  struct message_grab msq_grab_img;

  struct lpdr_data{
    long timestamp;

    char status[32];    // 수배종류
    char carNo[32];     // 차량정보
    // RECT
    int x;              // rect[0]
    int y;              // rect[1]    
    int endX;           // rect[2]
    int endY;           // rect[3]
  };
  struct message_lpdr{
      long msg_type;
      struct lpdr_data data;
  };
  struct message_lpdr msq_lpdr;

#ifdef EN_LIST_DISP
  // add. by ariari : 2022.05.20 - begin
  struct lpdr_info{
    char status[32];    // 수배종류
    char carNo[32];     // 차량정보
    
    // RECT
    int x;              // rect[0]
    int y;              // rect[1]    
    int endX;           // rect[2]
    int endY;           // rect[3]

    // score([0,100]) : add. by ariari : 2022.05.20
    int score;          // score [0,1]->[0,100]
  };
  struct message_lpdr_info{
      long msg_type;
      struct lpdr_info data;
  };
  struct message_lpdr_info msq_lpdr_info;

  struct message_lpdr_multi{
      long detect_num;
      struct lpdr_info data[10];
  };

  struct lpdr_result{
      long msg_type;
      struct message_lpdr_multi data;
  };
  struct lpdr_result msq_lpdr_result;
  // add. by ariari : 2022.05.20 - end
#endif


	int MessageQueueCreate();
  int MessageQueueInit();
	int MessageQueueQNum();
  int MessageQueueRead(char *data, int flag = IPC_NOWAIT);
	int MessageQueueWrite(char *data);
	int MessageQueueFree();
  //////////////////////////////////////////////////////////////////////////////////////////////////////	

private:

protected:

};