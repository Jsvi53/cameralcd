/*** 
 * @Date: 2024-09-16 23:05:26
 * @LastEditors: jsvi53
 * @LastEditTime: 2024-09-21 14:58:14
 * @FilePath: \cameraLcd\Core\Inc\utils.h
 */
/***
 * @Date: 2024-08-31 20:04:14
 * @LastEditors: jsvi53
 * @LastEditTime: 2024-09-17 22:52:01
 * @FilePath: \cameraLcd\Core\Inc\utils.h
 */
#ifndef __UTILS_H
#define __UTILS_H

#define IMG_WIDTH           240
#define IMG_HEIGHT          320
#define CHUNK_SIZE          65535
#define LINE_BUFFER_SIZE    (IMG_WIDTH * 2)
#define IMG_SIZE            (IMG_WIDTH * IMG_HEIGHT * 2)

typedef enum {
    frame_mode,  // Auto
    line_mode,   // Sunny
    pixel_mode,  // Cloudy
} ReceiveMode;

extern uint8_t              *image_buffer;
extern volatile uint8_t     image_received_flag;

int                         _write(int fd, char *ch, int len);
void                        image_receive_init(ReceiveMode mode);
void                        image_receive_run(void);
int                         process_image_data(uint8_t *data);

#endif