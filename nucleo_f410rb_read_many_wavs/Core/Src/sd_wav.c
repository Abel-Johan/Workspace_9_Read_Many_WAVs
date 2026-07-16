/*
 * sd_wav.c
 *
 *  Created on: 6 Jul 2026
 *      Author: Nehemiah Abel Cavanaugh Johan
 *
 *  Custom functions for reading WAV file
 *  Based on sd_read_file in sd_functions.c by ControllersTech
 */

#include "fatfs.h"
#include "sd_diskio_spi.h"
#include "sd_spi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ff.h"
#include "ffconf.h"

// Specifically for reading the first 12 bytes: The RIFF header chunk
int sd_wav_init(const char *filename, uint8_t *riff_header_chunk, UINT riff_header_size, UINT *bytes_read) {
	FIL file;
	*bytes_read = 0;

	printf("\nBeginning to read %s\r\n", filename);

	FRESULT res = f_open(&file, filename, FA_READ);
	if (res != FR_OK) {
		printf("f_open failed with code: %d\r\n", res);
		return res;
	}

	res = f_read(&file, riff_header_chunk, riff_header_size, bytes_read);
	if (res != FR_OK) {
		printf("f_read failed with code: %d\r\n", res);
		f_close(&file);
		return res;
	}

	res = f_close(&file);
	if (res != FR_OK) {
		printf("f_close failed with code: %d\r\n", res);
		return res;
	}

	return FR_OK;
}

// Specifically for reading the rest of the file
// Note the presence of f_lseek which allows us to increment along the part of the file we'd want to read
int sd_wav_read(const char *filename, uint8_t *buffer, UINT buf_size, int skip, UINT *bytes_read) {
	FIL file;
	*bytes_read = 0;

	FRESULT res = f_open(&file, filename, FA_READ);
	if (res != FR_OK) {
		printf("f_open failed with code: %d\r\n", res);
		return res;
	}

	// Move the file pointer to where you want it to start reading
	res = f_lseek(&file, skip);

	res = f_read(&file, buffer, buf_size, bytes_read);
	if (res != FR_OK) {
		printf("f_read failed with code: %d\r\n", res);
		f_close(&file);
		return res;
	}

	res = f_close(&file);
	if (res != FR_OK) {
		printf("f_close failed with code: %d\r\n", res);
		return res;
	}

	return FR_OK;

}
