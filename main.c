#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
/*
vector_set_capacity(vec, size)
vector_set_size(vec, size)
vector_capacity(vec)
vector_size(vec)
vector_empty(vec)
vector_grow(vec, count)
vector_pop_back(vec)
vector_erase(vec, i)
vector_free(vec)
vector_begin(vec)
vector_end(vec)
vector_push_back(vec, value)
*/
#define RFID_POINT_LEN              (18)
#define RFID_SIZE                   (256)
#define COMMAND_PACKET_MAX_LEN      (144)

typedef unsigned char  uint8_t;
typedef struct
{
    int byte[RFID_POINT_LEN];
}rfidpoint;

typedef struct
{
    int nid;
    int length;
    int speedlimit;
    int reserved;
    int flag;
}routenode;

typedef struct{
	uint8_t head[2];
	uint8_t len;  //从len开始计算的长度，包含len
	uint8_t type;
	uint8_t data[COMMAND_PACKET_MAX_LEN];
}command_packet_t;

int main(int argc, char *argv[])
{
    command_packet_t packet;
    rfidpoint *vmap = 0;
    rfidpoint rfidPoint;
    routenode *vroute = 0;
    int i = 0;
    int size = -1;
    int capacity = -1;

    packet.head[0] = 0x12;
    packet.head[1] = 0x34;
    packet.len = 144;
    packet.type = 0xa;
    for(i = 0; i < COMMAND_PACKET_MAX_LEN; i++)
    {
        packet.data[i] = i;
    }

    /*vector_grow - For internal use,
    ensures that the vector is at least
     <count> elements big*/
    vector_grow(vmap, RFID_SIZE);
    vector_grow(vroute, RFID_SIZE);

    /*vector_set_size - For internal use,
    sets the size variable of the vector*/
    vector_set_size(vmap, 0);
    vector_set_size(vroute, 0);

    for(i = 0; i < 100; i++)
    {
        memcpy(rfidPoint.byte, packet.data, RFID_POINT_LEN);
        vector_push_back(vmap, rfidPoint);
    }

    size = vector_size(vmap);
    capacity = vector_capacity(vmap);

    printf("size %d  capacity % d!\n", size, capacity);
    return 0;
}
