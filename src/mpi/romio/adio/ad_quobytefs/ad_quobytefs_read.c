/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/**
 *   Copyright 2019 Quobyte Inc. All rights reserved.
 *   Author: alexey@quobyte.com
 *   See COPYRIGHT notice in top-level directory.
 */


#include "adio.h"

#include "ad_quobytefs.h"

void ADIOI_QUOBYTEFS_ReadContig(ADIO_File fd, void *buf, int count,
                                MPI_Datatype datatype, int file_ptr_type,
                                ADIO_Offset offset, ADIO_Status * status, int *error_code)
{
    ssize_t err = -1;
    MPI_Count datatype_size;
    ADIO_Offset bytes_transfered;
    static char myname[] = "ADIOI_QUOBYTEFS_READCONTIG";

#ifdef AGGREGATION_PROFILE
    MPE_Log_event(5034, 0, NULL);
#endif
    MPI_Type_size_x(datatype, &datatype_size);
    bytes_transfered = datatype_size * (ADIO_Offset) count;

    if (file_ptr_type == ADIO_INDIVIDUAL) {
        offset = fd->fp_ind;
    }
#ifdef ADIOI_MPE_LOGGING
    MPE_Log_event(ADIOI_MPE_read_a, 0, NULL);
#endif
    int bytes_read = quobyte_read(fd->file_handle, buf, offset, bytes_transfered);
    fd->fp_sys_posn = offset + bytes_read;

    if (file_ptr_type == ADIO_INDIVIDUAL) {
        fd->fp_ind += bytes_read;
    }
#ifdef HAVE_STATUS_SET_BYTES
    MPIR_Status_set_bytes(status, datatype, bytes_transfered);
#endif
    *error_code = MPI_SUCCESS;
#ifdef AGGREGATION_PROFILE
    MPE_Log_event(5035, 0, NULL);
#endif
}
