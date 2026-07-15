/*
 * sd_wav.h
 *
 *  Created on: 6 Jul 2026
 *      Author: Nehemiah Abel Cavanaugh Johan
 */

#ifndef INC_SD_WAV_H_
#define INC_SD_WAV_H_

#include "fatfs.h"
#include <stdint.h>

int sd_wav_init(const char *filename, uint8_t *riff_header_chunk, UINT riff_header_size, UINT *bytes_read);
int sd_wav_read(const char *filename, uint8_t *buffer, UINT buf_size, int skip, UINT *bytes_read);


#endif /* INC_SD_WAV_H_ */
