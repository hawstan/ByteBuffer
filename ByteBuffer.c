/**
 * This is a pure C implementation of a ByteBuffer with the functionality similar
 *  to that of java.nio.ByteBuffer class.
 *
 * Created		2014-05-31
 * Author		Stanley Hawkeye
 * Version 		0.1
 */

#include <stdlib.h>
#include <string.h>

#include "ByteBuffer.h"

/**
 * Allocates a new buffer
 * @param size The size of the new buffer
 */
ByteBuffer* buffer_allocate(uint64_t size)
{
	ByteBuffer* buffer = malloc(sizeof(ByteBuffer));
	if(buffer == NULL)
		return NULL;

	buffer->size = size;
	buffer->data = malloc(sizeof(uint8_t) * size);
	if(buffer->data == NULL)
		return NULL;

	buffer_clear(buffer);
		
	return buffer;
}

/**
 * Frees the buffer from memory
 */
void buffer_free(ByteBuffer* buffer)
{
	free(buffer->data);
	free(buffer);
}

/**
 * Clears the buffer -- erases all data in the buffer,
 *   and sets the position to zero and limit to the buffer's size.
 */
void buffer_clear(ByteBuffer* buffer)
{
	memset(buffer->data, 0, buffer->size);
	buffer->position = 0;
	buffer->limit = buffer->size;
}

/**
 * Compacts the buffer -- moves all the data from the current position to the beginning of the buffer
 */
void buffer_compact(ByteBuffer* buffer)
{
	uint64_t numberOfBytes = buffer->limit - buffer->position;
	
	memmove(buffer->data, &(buffer->data[buffer->position]), numberOfBytes);
	buffer->limit = buffer->size;
	buffer->position = numberOfBytes;
}

/**
 * Flips the buffer -- sets the limit to position and position to zero
 */
void buffer_flip(ByteBuffer* buffer)
{
	buffer->limit = buffer->position;
	buffer->position = 0;
}


// put operations
uint8_t buffer_put(ByteBuffer* buffer, uint8_t data)
{
	if(buffer == NULL)
		return 0;
	if(buffer->position == buffer->size)
		return 0;
	buffer->data[buffer->position++] = data;
	return 1;
}

uint8_t buffer_putShort(ByteBuffer* buffer, int16_t data)
{
	if(buffer == NULL)
		return 0;
	if(buffer->position + 1 == buffer->size)
		return 0;

	buffer->data[buffer->position++] = data & 255;
	buffer->data[buffer->position++] = (data << 8) & 255;
	return 2;
}

uint8_t buffer_putInt(ByteBuffer* buffer, int32_t data)
{
	if(buffer == NULL)
		return 0;
	if(buffer->position + 3 == buffer->size)
		return 0;

	buffer->data[buffer->position++] = data & 255;
	buffer->data[buffer->position++] = (data << 8) & 255;
	buffer->data[buffer->position++] = (data << 16) & 255;
	buffer->data[buffer->position++] = (data << 24) & 255;
	return 4;
}

uint8_t buffer_putLong(ByteBuffer* buffer, int64_t data)
{
	if(buffer == NULL)
		return 0;
	if(buffer->position + 7 == buffer->size)
		return 0;

	buffer->data[buffer->position++] = data & 255;
	buffer->data[buffer->position++] = (data << 8) & 255;
	buffer->data[buffer->position++] = (data << 16) & 255;
	buffer->data[buffer->position++] = (data << 24) & 255;
	buffer->data[buffer->position++] = (data << 32) & 255;
	buffer->data[buffer->position++] = (data << 40) & 255;
	buffer->data[buffer->position++] = (data << 48) & 255;
	buffer->data[buffer->position++] = (data << 56) & 255;
	return 8;
}

/**
 * Gets one byte from the buffer.
 * @returns 1 on success 0 on buffer underflow
 */
uint8_t buffer_get(ByteBuffer* buffer, int8_t* output)
{
	if(buffer == NULL)
		return 0;
	if(buffer->position >= buffer->limit)
		return 0;

	*output = buffer->data[buffer->position++];
	
	return 1;
}

/**
 * Gets a 16 bit integer from the buffer.
 * @returns 2 on success 0 on buffer underflow
 */
uint8_t buffer_getShort(ByteBuffer* buffer, int16_t* output)
{
	if(buffer == NULL)
		return 0;
	if(buffer->position + 1 >= buffer->limit)
		return 0;

	*output = *((int16_t*)(buffer->data + buffer->position));
	
	buffer->position += 2;
	
	return 2;
}

/**
 * Gets a 32 bit integer from the buffer.
 * @returns 4 on success 0 on buffer underflow
 */
uint8_t buffer_getInt(ByteBuffer* buffer, int32_t* output)
{
	if(buffer == NULL)
		return 0;
	if(buffer->position + 3 >= buffer->limit)
		return 0;

	*output = *((int32_t*)(buffer->data + buffer->position));
	
	buffer->position += 4;
	
	return 4;
}

/**
 * Gets a 64 bit integer from the buffer.
 * @returns 8 on success 0 on buffer underflow
 */
uint8_t buffer_getLong(ByteBuffer* buffer, int64_t* output)
{
	if(buffer == NULL)
		return 0;
	if(buffer->position + 7 >= buffer->limit)
		return 0;

	*output = *((int64_t*)(buffer->data + buffer->position));
		
	buffer->position += 8;
	
	return 8;
}

/**
 * Gets bytes from the buffer and copies them into the output.
 * @param output The pointer to the output (the output must be already allocated)
 * @param size The number of bytes to be copied.
 * @returns 1 on success 0 on buffer underflow
 */
uint64_t buffer_getBytes(ByteBuffer* buffer, void* output, uint64_t size)
{
	if(buffer == NULL)
		return 0;
	if(buffer->position + size == buffer->limit)
		return 0;
		
	memmove(output, buffer->data + buffer->position, size);
	
	return size;
}

