// minia.d.ts
//
// `Minia` - A C++ tool for feature transformation and hashing
// Copyright (C) 2019 - present Uopensail <timepi123@gmail.com>
// This software is distributed under the GNU Affero General Public License
// (AGPL3.0) For more information, please visit:
// https://www.gnu.org/licenses/agpl-3.0.html
//
// This program is free software: you are free to redistribute and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Refer to the
// GNU Affero General Public License for more details.
//

/**
 * @typedef {number} Float
 * @description Represents a floating-point number type for better semantic clarity
 */
export type Float = number;

/**
 * @interface DataTypeValue
 * @description Represents an Emscripten enumeration value with its numeric identifier
 */
export interface DataTypeValue {
  /** @description The numeric value of the enumeration */
  readonly value: number;
}

/**
 * @interface DataTypeEnum
 * @description Emscripten-exported DataType enumeration structure containing all data type definitions
 */
export interface DataTypeEnum {
  /** @description 64-bit integer data type */
  readonly kInt64: DataTypeValue;

  /** @description 32-bit floating-point data type */
  readonly kFloat32: DataTypeValue;

  /** @description String data type */
  readonly kString: DataTypeValue;

  /** @description Array of 64-bit integers data type */
  readonly kInt64s: DataTypeValue;

  /** @description Array of 32-bit floating-point numbers data type */
  readonly kFloat32s: DataTypeValue;

  /** @description Array of strings data type */
  readonly kStrings: DataTypeValue;

  /** @description Error data type for invalid or failed operations */
  readonly kError: DataTypeValue;

  /** @description Lookup table for reverse mapping from numeric values to DataTypeValue objects */
  readonly values: Readonly<Record<number, DataTypeValue>>;
}

/**
 * @type FeatureValue
 * @description Union type representing all possible feature values
 */
export type FeatureValue = bigint | Float | string | bigint[] | Float[] | string[];

/**
 * @interface Feature
 * @description Represents a single feature with its type and value
 */
export interface Feature {
  /** 
   * @description The data type identifier corresponding to the feature value
   * @note Uses the numeric value from DataTypeEnum entries, excluding the 'values' property
   */
  readonly type: DataTypeEnum[keyof Omit<DataTypeEnum, "values">]["value"];

  /** 
   * @description The actual feature value, type must match the specified type field
   */
  readonly value: FeatureValue;
}

/**
 * @type Features
 * @description Collection of named features indexed by string keys
 */
export type Features = Record<string, Feature>;

/**
 * @interface JSMiniaInstance
 * @description Interface defining the contract for JSMinia instances
 */
export interface JSMiniaInstance {
  /**
   * @description Processes input features and returns computed results
   * @param {Features} features - Input features to process
   * @returns {Features} Processed output features
   */
  call(features: Features): Features;
}

/**
 * @class JSMinia
 * @description Main class for feature processing using WebAssembly backend
 * @implements {JSMiniaInstance}
 */
export declare class JSMinia implements JSMiniaInstance {
  /**
   * @description Creates a new JSMinia instance
   * @param {string[]} exprs - Expression definitions or configuration (string[])
   */
  constructor(exprs: string[]);

  /**
   * @description Processes input features and returns computed results
   * @param {Features} features - Input features to process
   * @returns {Features} Processed output features
   */
  call(features: Features): Features;

  /**
   * @description Explicitly destroys the instance and frees associated memory
   * @note This is automatically added by Emscripten for proper memory management
   * @warning Call this method when the instance is no longer needed to prevent memory leaks
   */
  delete(): void;
}

/**
 * @interface JSMiniaModuleInitOptions
 * @description Configuration options for module initialization
 */
export interface JSMiniaModuleInitOptions {
  /** @description WebAssembly module location or URL */
  locateFile?: (path: string, prefix: string) => string;

  /** @description Memory initialization options */
  wasmMemory?: WebAssembly.Memory;

  /** @description Additional Emscripten module options */
  [key: string]: unknown;
}

/**
 * @interface JSMiniaModule
 * @description Main module interface exposing DataType enumeration and JSMinia class
 */
export interface JSMiniaModule {
  /** @description DataType enumeration for type identification */
  readonly DataType: DataTypeEnum;

  /** @description JSMinia class constructor */
  readonly JSMinia: typeof JSMinia;
}

/**
 * @function JSMiniaModuleInit
 * @description Factory function to initialize the JSMinia WebAssembly module
 * @param {JSMiniaModuleInitOptions} [options] - Optional initialization configuration
 * @returns {Promise<JSMiniaModule>} Promise resolving to the initialized module
 * @example
 * ```typescript
 * const module = await JSMiniaModuleInit();
 * const minia = new module.JSMinia(expressions);
 * const results = minia.call(inputFeatures);
 * minia.delete(); // Clean up when done
 * ```
 */
declare function JSMiniaModuleInit(options?: JSMiniaModuleInitOptions): Promise<JSMiniaModule>;

export default JSMiniaModuleInit;
