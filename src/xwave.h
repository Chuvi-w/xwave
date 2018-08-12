#ifndef XWAVE_H_INCLUDED
#define XWAVE_H_INCLUDED

//для работы с файлами
#include <stdio.h>

#define XWAVE_MAX_PATH 260
#define XWAVE_OK 0x01
#define XWAVE_ERROR 0x00
#define XWAVE_SAVE_FILE_ONLINE 0x01

//struct _xwave_wave_file;
//typedef struct _xwave_wave_file xwave_wave_file;
typedef struct {
    unsigned long sample_rate;                              /**< Частота дискретизации. 8000 Гц, 44100 Гц и т.д. */
    unsigned long byte_rate;                                /**< Количество байт, переданных за секунду воспроизведения. */
    unsigned short bits_per_sample;                         /**< Количество бит в сэмпле. Так называемая “глубина” или точность звучания. 8 бит, 16 бит и т.д. */
    unsigned short num_channels;                            /**< Количество каналов. Моно = 1, Стерео = 2 и т.д. */
    FILE* fp_save;                                          /**<  */
    unsigned short block_align;                             /**< Количество байт для одного сэмпла, включая все каналы */
    unsigned long subchunk2_size;                           /**< Количество байт в области данных. */
    unsigned long chunk_size;                               /**< Это оставшийся размер цепочки, начиная с этой позиции. Иначе говоря, это размер файла – 8, то есть, исключены поля chunkId и chunkSize. */
    unsigned char len_data_type;                            /**< длина тиа данных */
    char file_name[XWAVE_MAX_PATH];                         /**< Имя файла */
    char* data;
} xwave_wave_file;

/** \brief Инициализация структуры wav-файла
 *
 * \param wave_file структура файла wav
 * \param file_name имя файла
 * \param sample_rate Частота дискретизации
 * \param bits_per_sample Количество бит в сэмпле
 * \param num_channels Количество каналов
 *
 */
void xwave_init_wave_file(xwave_wave_file* wave_file, const char* file_name, unsigned long sample_rate, unsigned short bits_per_sample, unsigned short num_channels);

/** \brief Создать wav файл для онлайн записи
 *
 * \param wave_file структура файла wav
 * \return вернет XWAVE_OK если удалось создать файл
 *
 */
int xwave_create_wave_file(xwave_wave_file* wave_file);

/** \brief Записать сэмпл в wav файл
 *
 * \param wave_file структура файла wav
 * \param data данные для сохранения
 *
 */
void xwave_write_sample_wave_file(xwave_wave_file* wave_file, void* data);

/** \brief Записать блок данных в wav файл
 *
 * \param wave_file структура файла wav
 * \param data данные для сохранения
 * \param len длина данных
 *
 */
void xwave_write_data_block_wave_file(xwave_wave_file* wave_file, void* data, unsigned long len);

void xwave_close_wave_file(xwave_wave_file* wave_file);

void xwave_get_impulses_mono(void* data, unsigned long sample_rate, unsigned short bits_per_sample, double period, double amplitude, unsigned long len);

void xwave_get_pause_mono(void* data, unsigned long sample_rate, unsigned short bits_per_sample, unsigned long len);

void xwave_get_multiple_impulses_mono(void* data, unsigned long sample_rate, unsigned short bits_per_sample, double* period, double* amplitude, unsigned short num_impulses, unsigned long len);

void xwave_get_multiple_damped_impulses_mono(void* data, unsigned long sample_rate, unsigned short bits_per_sample, double* period, double* amplitude, unsigned short num_impulses, unsigned long len);

#endif // XWAVE_H_INCLUDED