#ifndef CILENT_H
#define CILENT_H
//network
#define ONLINE		1
#define OFFLINE		0
#define ERROR		11
#define MAXDATASIZE	1024
#define SERVPORT 3333
#define SERVPORT_FILE 3334
#define NEW_CLIENT 1000
#define BACKLOG 1
//command
#define HANDSHAKE	1
#define GET_INFO	2
#define SEND_PARA	3
#define SEND_FILE	4
#define FILE_PACKAGE 40
#define START_PRINT	5
#define LAYERS_STATUS   6
#define HUNG_CMD	7
#define RECOVER		8
#define WORK_OVER 11
#define PROJ_CMD    12
#define SEND_FILE_JPEG 13
#define HEARTBEAT   14
#define RESET_PRINTER 15
#define NONE_CMD 21
//motor debug
#define MOTOR_MOVE	10
#define MOTOR_TO_UP	1001
#define MOTOR_TO_DOWN	1002
//project debug
#define PROJ_ON     100
#define PROJ_OFF    101
#define PROJ_DEBUG  102
#define PROJ_LAYER  103
//feedback
#define WORK_NORMAL	17
#define WORK_ABNORMAL	18
#define COMMAND_INVALID 16
#define COMMAND_VALID 19
#define TCP_READY 20
#define FINISH_MARK	2013
//file name on server
#define FILENAME	"test.xml"
#define FILENAME2 "jpegtest.jpg"
//status
#define IDLE 0
#define BUSY 1
#define NONE -1
#define PRINTING 2
#define HUNG 3
#define DEBUG 4
#define INIT 5

#define DIR_DOWN    0
#define DIR_UP      1

//debug for chenpeng-2014-7-18
#define PRINT_BASE 911
#define SEND_BASE_PARA 912
#define MOVE_TOP 913
#define MOVE_BOTTON 914

//define by chenpeng 2014-10-29
#define THICK_HIGHT 916
#define THICK_MID   917
#define THICK_LOW   918

#define SPOT_G  919
#define SPOT_HT 920
#define MAKERJUICE_G 921
#define MAKERJUICE_SF 922


typedef struct _connect_t
{
    int status;
    int magic;
} connect_t;

typedef struct _info_t
{
    int version;
    int max_high;
    int sockfd;
} info_t;
typedef struct _parameters_t
{
    int Thick_config;
    int Resin_config;
//    int cure_time;
//    int freze_time;
//    int layers;
//    int thickness;

//    int base_cure_time;
//    int base_freze_time;
//    int base_thickness;
//    int gap_len;

} para_t;
typedef struct _cmd_t
{
    int cmd;
    int buf_len;//the length of struct
    char buf[MAXDATASIZE];
}cmd_t;

typedef struct _feedback_t
{
    int status;
    int buf_len;//the length of struct
    char buf[MAXDATASIZE];
}feedback_t;


#endif // CILENT_H
