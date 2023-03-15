#include<stdio.h>
#include "obs_data.h"

static FILE *fp;

void create_file(char *filename){
    fp = fopen(filename,"w");
}

int write_header(obs_header_t *obs_header){
    // wirte the file size to the beginning of the file.
    // it should be a 4B value.
    fwrite(&(obs_header->HDRSIZE), sizeof(unsigned int), 1, fp);
    // write json header to the file
    fprintf(fp, "{\n");
    fprintf(fp, " \"sw_ver\":\"%s\",      \
                  \"fpg\": \"%s\",       \
                  \"time\": %10f,        \
                  \"sample_freq\": %4u,   \
                  \"acclen\": %4u,       \
                  \"adc_coarse_gain\": %4u,\
                  \"fft_shift\": %5u,     \
                  \"data_sel\": %4u,      \
                  \"scaling\": %4u,      \
                  \"spec_coeff\": %4u,    \
                  \"adc_delay_0\": %4u,    \
                  \"adc_delay_1\": %4u,    \
                  \"adc_delay_2\": %4u,    \
                  \"adc_delay_3\": %4u,    \
                  \"adc_delay_4\": %4u,    \
                  \"adc_delay_5\": %4u,    \
                  \"adc_delay_6\": %4u,    \
                  \"adc_delay_7\": %4u,     \
                  \"rf_lo_hz\" : %10u,    \
                  \"target_ra\":\"%s\",  \
                  \"target_dec\":\"%s\",  \
                  \"pointing_el\": %2.2f,    \
                  \"pointing_az\": %2.2f,    \
                  \"pointing_updated\": %10f \
                }", obs_header->SWVER,      \
                    obs_header->FPG,        \
                    obs_header->TIME,       \
                    obs_header->SAMPLEFREQ, \
                    obs_header->ACCLEN,     \
                    obs_header->ADCCOARSEGAIN,\
                    obs_header->FFTSHIFT,   \
                    obs_header->DATASEL,    \
                    obs_header->SCALING,    \
                    obs_header->SPECCOEFF,  \
                    obs_header->ADCDELAY[0],\
                    obs_header->ADCDELAY[1],\
                    obs_header->ADCDELAY[2],\
                    obs_header->ADCDELAY[3],\
                    obs_header->ADCDELAY[4],\
                    obs_header->ADCDELAY[5],\
                    obs_header->ADCDELAY[6],\
                    obs_header->ADCDELAY[7],\
                    obs_header->RF_LO_HZ,   \
                    obs_header->TARGET_RA_DEG,\
                    obs_header->TARGET_DEC_DEG,\
                    obs_header->POINTING_EL_DEG,\
                    obs_header->POINTING_AZ_DEG,\
                    obs_header->POINTING_UPDATED
                    );
    // we use the first HDR_SIZE bytes for header
    return fseek(fp, HDR_SIZE + 4, SEEK_SET);
}

int write_data(void *data, int nbytes){
    fwrite((char *)data, 1, nbytes, fp);
}

void close_file(){
    fclose(fp);
}
