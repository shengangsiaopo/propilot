
#include "options.h"
#include "libUDB_defines.h"
// #error( "sdf", SERIAL_OUTPUT_TYPE );

#if (SERIAL_OUTPUT_FORMAT == SERIAL_DEBUG)
#error SERIAL_DEBUG
#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_ARDUSTATION )
#error SERIAL_ARDUSTATION
#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_OSD_REMZIBI )
#error SERIAL_OSD_REMZIBI
#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_MAGNETOMETER )
#error SERIAL_MAGNETOMETER
#elif ( SERIAL_OUTPUT_FORMAT == SERIAL_STATUS )
#error SERIAL_STATUS
#elif (( SERIAL_OUTPUT_FORMAT == SERIAL_UDB ) || ( SERIAL_OUTPUT_FORMAT == SERIAL_UDB_EXTRA ))
#error (( SERIAL_OUTPUT_FORMAT == SERIAL_UDB ) || ( SERIAL_OUTPUT_FORMAT == SERIAL_UDB_EXTRA ))
#else // If SERIAL_OUTPUT_FORMAT is set to SERIAL_NONE, or is not set
#error else
#endif
