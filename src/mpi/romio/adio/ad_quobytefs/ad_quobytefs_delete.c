/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/**
 *   Copyright 2019 Quobyte Inc. All rights reserved.
 *   Author: alexey@quobyte.com
 *   See COPYRIGHT notice in top-level directory.
 */


#include "adio.h"

#include "ad_quobytefs.h"

void ADIOI_QUOBYTEFS_Delete(const char *path, int *error_code)
{
    ADIOI_QUOBYTEFS_CreateAdapter(path, error_code);
    static char myname[] = "ADIOI_QUOBYTEFS_DELETE";

    if (quobyte_unlink(GetVolumeAndPath(path))) {
        *error_code = ADIOI_Err_create_code(myname, path, errno);
        return;
    }
    *error_code = MPI_SUCCESS;
}
