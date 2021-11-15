#!/bin/sh

COMMIT=$(git rev-list --max-count=1 HEAD | cut -b 1-8) || exit 1

cat <<EOF
#ifndef VERSION_C
#define VERSION_C

#include "../version.h"

PGM_P version(void)
{
  return PSTR("${COMMIT}");
}

#endif // VERSION_C
EOF
