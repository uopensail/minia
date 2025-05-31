package main

import (
	"fmt"
	"gominia/wrapper"
	"os"
)

func main() {
	// Initialize a new Minia client with the configuration path
	client := wrapper.NewMiniaClient("../config/config.toml")
	defer client.Release() // Ensure resources are released when done

	// Execute the Minia call with a FlatBuffers input string
	data, _ := os.ReadFile("../data/data.bin")
	featureSet := client.Call(data)
	defer featureSet.Release() // Ensure feature resources are released

	// Iterate over the features in the FeatureSet
	for key, feature := range featureSet.Features {
		// Attempt to retrieve the string slice from the feature
		if feature.Type == wrapper.TypeFloat32 {
			value, _ := feature.GetFloat32()
			fmt.Printf("Key: %s, Value: %f\n", key, value)
		} else if feature.Type == wrapper.TypeInt64 {
			value, _ := feature.GetInt64()
			fmt.Printf("Key: %s, Value: %d\n", key, value)
		} else if feature.Type == wrapper.TypeString {
			value, _ := feature.GetString()
			fmt.Printf("Key: %s, Value: %s\n", key, value)
		}
	}
}
