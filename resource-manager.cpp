/*
 * Resource loading:
 *  -get base executable path
 *  -must know relative path to config file
 *      -most likely local to the executable
 *  -config points to search directories; load into search algorithm
 *  -follow Resource Acquisition Is Initialization (RAII) until I find
 *      something better
 *
 * Cross-platform file name/path handling:
 *  -covert to from utf-8 to utf-16 for windows
 *
 *
 */

// - load current directory location
// - load config file for search paths
//
// - get utf-8 file name
// - search for file in search directories
// - load appropriately using extension as key
//
// should support:
//  -basic image and audio file types
//  -compressed formats
