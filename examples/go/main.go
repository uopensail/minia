package main

import (
	"fmt"
	"gominia/wrapper"
)

func main() {
	// Initialize a new Minia client with the configuration path
	client := wrapper.NewMiniaClient("../config/config_2.toml")
	defer client.Release() // Ensure resources are released when done

	// Execute the Minia call with a JSON input string
	featureSet := client.Call(`{"h": {"type": 3, "value": [4,8]}}`)
	defer featureSet.Release() // Ensure feature resources are released

	// Iterate over the features in the FeatureSet
	for key, feature := range featureSet.Features {
		// Attempt to retrieve the string slice from the feature
		if values, err := feature.GetStringSlice(); err == nil {
			fmt.Printf("Key: %s, Value: %v\n", key, values)
		} else {
			fmt.Printf("Key: %s, Error: %v\n", key, err)
		}
	}
}
