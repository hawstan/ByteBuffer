/**
 * This is a pure C implementation of a ByteBuffer with the functionality similar
 *  to that of java.nio.ByteBuffer class.
 *
 * Created		2014-05-31
 * Author		Stanley Hawkeye
 * Version 		0.1
 */

#ifndef BYTE_BUFFER_H
#define BYTE_BUFFER_H

#include <stdint.h>

typedef struct
{
	uint64_t size;
	uint8_t* data;
	uint64_t position;
	uint64_t limit;
} ByteBuffer;

/**
 * Allocates a new buffer
 * @param size The size of the new buffer
 */
ByteBuffer* buffer_allocate(uint64_t size);

/**
 * Frees the buffer from memory
 */
void buffer_free(ByteBuffer* buffer);

/**
 * Clears the buffer -- sets the position to zero and limit to the buffer's size.
 */
void buffer_clear(ByteBuffer* buffer);

/**
 * Compacts the buffer -- moves all the data from the current position to the beginning of the buffer
 */
void buffer_compact(ByteBuffer* buffer);

/**
 * Flip the buffer -- sets the limit to position and position to zero
 */
void buffer_flip(ByteBuffer* buffer);



uint8_t buffer_put(ByteBuffer* buffer, uint8_t data);

uint8_t buffer_putShort(ByteBuffer* buffer, int16_t data);

uint8_t buffer_putInt(ByteBuffer* buffer, int32_t data);

uint8_t buffer_putLong(ByteBuffer* buffer, int64_t data);


/**
 * Gets one byte from the buffer.
 * @returns 1 on success 0 on buffer underflow
 */
uint8_t buffer_get(ByteBuffer* buffer, int8_t* output);

/**
 * Gets a 16 bit integer from the buffer.
 * @returns 2 on success 0 on buffer underflow
 */
uint8_t buffer_getShort(ByteBuffer* buffer, int16_t* output);

/**
 * Gets a 32 bit integer from the buffer.
 * @returns 4 on success 0 on buffer underflow
 */
uint8_t buffer_getInt(ByteBuffer* buffer, int32_t* output);

/**
 * Gets a 64 bit integer from the buffer.
 * @returns 8 on success 0 on buffer underflow
 */
uint8_t buffer_getLong(ByteBuffer* buffer, int64_t* output);

/**
 * Gets bytes from the buffer and copies them into the output.
 * @param output The pointer to the output (the output must be already allocated)
 * @param size The number of bytes to be copied.
 * @returns 1 on success 0 on buffer underflow
 */
uint64_t buffer_getBytes(ByteBuffer* buffer, void* output, uint64_t size);

#endif
