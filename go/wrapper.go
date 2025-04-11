package wrapper

/*
#cgo CXXFLAGS: -std=c++17 -I/usr/local/include/antlr4-runtime -I${SRCDIR}/include
#cgo LDFLAGS: -lantlr4-runtime -static-libstdc++

// 内联项目 C++ 源码
#include "src/minia.cc"
#include <stdlib.h>
#include "cminia.h"
*/
import "C"
import (
	"fmt"
	"unsafe"
)

/**
 * DataType represents the type identifier for feature data
 *
 * Enumeration of supported data types:
 * - TypeInt64: 64-bit integer value
 * - TypeFloat32: 32-bit floating point value
 * - TypeString: String value
 * - TypeInt64Slice: Slice of 64-bit integers
 * - TypeFloat32Slice: Slice of 32-bit floats
 * - TypeStringSlice: Slice of strings
 * - TypeError: Error type indicator
 */
type DataType int32

const (
	TypeInt64 DataType = iota
	TypeFloat32
	TypeString
	TypeInt64Slice
	TypeFloat32Slice
	TypeStringSlice
	TypeError DataType = 127
)

/**
 * Feature represents a typed data container with C memory management
 *
 * Contains two main components:
 * - Type: Data type identifier (DataType enum)
 * - Data: Pointer to the underlying C memory allocation
 */
type Feature struct {
	Type DataType
	Data unsafe.Pointer
}

/**
 * GetInt64 retrieves int64 value from the Feature
 * @return (int64, error) tuple containing:
 *         - Retrieved value if type matches
 *         - Type mismatch error otherwise
 */
func (f *Feature) GetInt64() (int64, error) {
	if f.Type != TypeInt64 {
		return 0, fmt.Errorf("type mismatch: expected %d got %d", TypeInt64, f.Type)
	}
	return *(*int64)(f.Data), nil
}

/**
 * GetFloat32 retrieves float32 value from the Feature
 * @return (float32, error) tuple containing:
 *         - Retrieved value if type matches
 *         - Type mismatch error otherwise
 */
func (f *Feature) GetFloat32() (float32, error) {
	if f.Type != TypeFloat32 {
		return 0.0, fmt.Errorf("type mismatch: expected %d got %d", TypeFloat32, f.Type)
	}
	return *(*float32)(f.Data), nil
}

/**
 * GetString retrieves string value from the Feature
 * @return (string, error) tuple containing:
 *         - Retrieved string if type matches
 *         - Type mismatch error otherwise
 *
 */
func (f *Feature) GetString() (string, error) {
	if f.Type != TypeString {
		return "", fmt.Errorf("type mismatch: expected %d got %d", TypeString, f.Type)
	}
	return *(*string)(f.Data), nil
}

/**
 * GetInt64Slice retrieves a slice of int64 values from the Feature
 * @return ([]int64, error) tuple containing:
 *         - Retrieved slice if type matches
 *         - Type mismatch error otherwise
 */
func (f *Feature) GetInt64Slice() ([]int64, error) {
	if f.Type != TypeInt64Slice {
		return nil, fmt.Errorf("type mismatch: expected %d got %d", TypeInt64Slice, f.Type)
	}
	return *(*[]int64)(f.Data), nil
}

/**
 * GetFloat32Slice retrieves a slice of float32 values from the Feature
 * @return ([]float32, error) tuple containing:
 *         - Retrieved slice if type matches
 *         - Type mismatch error otherwise
 */
func (f *Feature) GetFloat32Slice() ([]float32, error) {
	if f.Type != TypeFloat32Slice {
		return nil, fmt.Errorf("type mismatch: expected %d got %d", TypeFloat32Slice, f.Type)
	}
	return *(*[]float32)(f.Data), nil
}

/**
 * GetStringSlice retrieves a slice of string values from the Feature
 * @return ([]string, error) tuple containing:
 *         - Retrieved slice if type matches
 *         - Type mismatch error otherwise
 */
func (f *Feature) GetStringSlice() ([]string, error) {
	if f.Type != TypeStringSlice {
		return nil, fmt.Errorf("type mismatch: expected %d got %d", TypeStringSlice, f.Type)
	}
	return *(*[]string)(f.Data), nil
}

/**
 * Release frees the underlying C memory associated with the Feature
 *
 * Calls C.minia_del_feature with proper type information
 */
func (f *Feature) Release() {
	C.minia_del_feature(f.Data, C.int32_t(f.Type))
}

/**
 * FeatureSet manages a collection of Features and their C resources
 *
 * Contains:
 * - instancePtr: Pointer to the C feature set instance
 * - features: Map of feature names to Feature objects
 */
type FeatureSet struct {
	instancePtr unsafe.Pointer
	Features    map[string]Feature
}

/**
 * NewFeatureSet creates a new FeatureSet instance
 * @param ptr C pointer to feature set
 * @param featureNames List of feature names to retrieve
 * @return *FeatureSet initialized feature set
 *
 * Automatically handles:
 * - C string conversions
 * - Feature type detection
 * - Memory management for temporary C strings
 */
func NewFeatureSet(ptr unsafe.Pointer, featureNames []string) *FeatureSet {
	featureMap := make(map[string]Feature, len(featureNames))

	for _, name := range featureNames {
		cName := C.CString(name)
		defer C.free(unsafe.Pointer(cName))

		var dtype DataType
		cFeature := C.minia_get_feature(
			ptr,
			cName,
			(*C.int32_t)(unsafe.Pointer(&dtype)),
		)

		featureMap[name] = Feature{
			Type: dtype,
			Data: cFeature,
		}
	}

	return &FeatureSet{
		instancePtr: ptr,
		Features:    featureMap,
	}
}

/**
 * Release cleans up all C resources in the FeatureSet
 *
 * Execution sequence:
 * 1. Releases all contained Feature objects
 * 2. Calls C.minia_del_features on the instance pointer
 */
func (fs *FeatureSet) Release() {
	for _, feature := range fs.Features {
		feature.Release()
	}
	C.minia_del_features(fs.instancePtr)
}

/**
 * MiniaClient manages the connection to the C minia library
 *
 * Contains:
 * - instancePtr: Pointer to the C minia instance
 * - featuresListPtr: Pointer to C features list
 * - featureNames: Go-accessible list of feature names
 */
type MiniaClient struct {
	instancePtr     unsafe.Pointer
	featuresListPtr unsafe.Pointer
	featureNames    []string
}

/**
 * NewMiniaClient initializes a new Minia client instance
 * @param configPath Path to configuration file
 * @return *MiniaClient initialized client instance
 *
 * Handles:
 * - Configuration file path conversion to C string
 * - Initial C instance creation
 * - Feature list retrieval
 */
func NewMiniaClient(configPath string) *MiniaClient {
	cConfig := C.CString(configPath)
	defer C.free(unsafe.Pointer(cConfig))

	instance := C.minia_create(cConfig)
	features := C.minia_features(instance)

	return &MiniaClient{
		instancePtr:     instance,
		featuresListPtr: features,
		featureNames:    *(*[]string)(features),
	}
}

/**
 * Call executes a Minia request with provided input
 * @param input Input string for processing
 * @return *FeatureSet containing results
 *
 * Handles:
 * - Input string conversion to C string
 * - Result feature set creation
 */
func (mc *MiniaClient) Call(input string) *FeatureSet {
	cInput := C.CString(input)
	defer C.free(unsafe.Pointer(cInput))

	return NewFeatureSet(
		C.minia_call(mc.instancePtr, cInput),
		mc.featureNames,
	)
}

/**
 * Release cleans up all C resources associated with the client
 *
 * Execution sequence:
 * 1. Releases features list memory
 * 2. Releases main instance memory
 */
func (mc *MiniaClient) Release() {
	C.minia_del_feature(mc.featuresListPtr, C.int32_t(TypeStringSlice))
	C.minia_release(mc.instancePtr)
}
