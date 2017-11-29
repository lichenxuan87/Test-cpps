/*
 * main.c
 *
 *  Created on: Nov 23, 2017
 *      Author: knowyou
 */


#include "vehicle.h"
#include "stddef.h"
#include "stdio.h"
#include "string.h"

static char VEHICLE_MAKE[] = "android_car";
static char BANMA_MAKE[] = "BANMA Car";
#define RADIO_PRESET_NUM 6
#define RADIO_BAND_FM 0
#define RADIO_BAND_AM 1

static vehicle_prop_config_t CONFIGS[] = {
    {
        .prop = VEHICLE_PROPERTY_INFO_MAKE,
        .access = VEHICLE_PROP_ACCESS_READ,
        .change_mode = VEHICLE_PROP_CHANGE_MODE_STATIC,
        .value_type = VEHICLE_VALUE_TYPE_STRING,
        .min_sample_rate = 0,
        .max_sample_rate = 0,
        .hal_data = NULL,
    },
    {
        .prop = VEHICLE_PROPERTY_GEAR_SELECTION,
        .access = VEHICLE_PROP_ACCESS_READ,
        .change_mode = VEHICLE_PROP_CHANGE_MODE_ON_CHANGE,
        .value_type = VEHICLE_VALUE_TYPE_INT32,
        .min_sample_rate = 0,
        .max_sample_rate = 0,
        .hal_data = NULL,
    },
    {
        .prop = VEHICLE_PROPERTY_DRIVING_STATUS,
        .access = VEHICLE_PROP_ACCESS_READ,
        .change_mode = VEHICLE_PROP_CHANGE_MODE_ON_CHANGE,
        .value_type = VEHICLE_VALUE_TYPE_INT32,
        .min_sample_rate = 0,
        .max_sample_rate = 0,
        .hal_data = NULL,
    },
    {
        .prop = VEHICLE_PROPERTY_PARKING_BRAKE_ON,
        .access = VEHICLE_PROP_ACCESS_READ,
        .change_mode = VEHICLE_PROP_CHANGE_MODE_ON_CHANGE,
        .value_type = VEHICLE_VALUE_TYPE_BOOLEAN,
        .min_sample_rate = 0,
        .max_sample_rate = 0,
        .hal_data = NULL,
    },
    {
        .prop = VEHICLE_PROPERTY_PERF_VEHICLE_SPEED,
        .access = VEHICLE_PROP_ACCESS_READ,
        .change_mode = VEHICLE_PROP_CHANGE_MODE_CONTINUOUS,
        .value_type = VEHICLE_VALUE_TYPE_FLOAT,
        .min_sample_rate = 0.1,
        .max_sample_rate = 10.0,
        .hal_data = NULL,
    },
    {
        .prop = VEHICLE_PROPERTY_RADIO_PRESET,
        .access = VEHICLE_PROP_ACCESS_READ_WRITE,
        .change_mode = VEHICLE_PROP_CHANGE_MODE_ON_CHANGE,
        .value_type = VEHICLE_VALUE_TYPE_INT32_VEC4,
        .vehicle_radio_num_presets = RADIO_PRESET_NUM,
        .min_sample_rate = 0,
        .max_sample_rate = 0,
        .hal_data = NULL,
    },
};

vehicle_prop_config_t* find_config(int prop) {
    unsigned int i;
    for (i = 0; i < sizeof(CONFIGS) / sizeof(vehicle_prop_config_t); i++) {
        if (CONFIGS[i].prop == prop) {
            return &CONFIGS[i];
        }
    }
    return NULL;
}

static int alloc_vehicle_str_from_cstr(const char* string, vehicle_str_t* vehicle_str) {
    int len = strlen(string);
    vehicle_str->data = (uint8_t*) malloc(len);
    if (vehicle_str->data == NULL) {
        return -ENOMEM;
    }
    memcpy(vehicle_str->data, string, len);
    vehicle_str->len = len;
    return 0;
}

int64_t getTime()
{
    // Need to implement get nano time here
    return 0;
}

static vehicle_prop_config_t const * listProperties(
        int* num_properties) {
    printf("vdev_list_properties.");

    *num_properties = sizeof(CONFIGS) / sizeof(vehicle_prop_config_t);
    return CONFIGS;
}



static int getProperty(vehicle_prop_value_t* data) {
    //TODO all data supporting read should support get
    if (!data) {
        printf("getProperty: Data cannot be null.");
        return -EINVAL;
    }
    vehicle_prop_config_t* config = find_config(data->prop);
    if (config == NULL) {
        printf("getProperty: cannot find config 0x%x", data->prop);
        return -EINVAL;
    }
    data->value_type = config->value_type;
    // for STATIC type, time can be just 0 instead
    data->timestamp = getTime();
    int r;
    switch (data->prop) {
        case VEHICLE_PROPERTY_INFO_MAKE:
            r = alloc_vehicle_str_from_cstr(VEHICLE_MAKE, &(data->value.str_value));
            if (r != 0) {
                printf("getProperty: alloc failed");
                return r;
            }
            break;

        case VEHICLE_PROPERTY_RADIO_PRESET: {
              int radio_preset = data->value.int32_array[0];
              if (radio_preset < VEHICLE_RADIO_PRESET_MIN_VALUE ||
                  radio_preset >= RADIO_PRESET_NUM) {
                  printf("%s Invalid radio preset: %d\n", __func__, radio_preset);
                  return -1;
              }
              printf("%s Radio Preset number: %d\n", __func__, radio_preset);
              int32_t selector = radio_preset % 2 == 0;
              // Populate the channel and subchannel to be some variation of the
              // preset number for mocking.

              // Restore the preset number.
              data->value.int32_array[0] = radio_preset;
              // Channel type values taken from
              // system/core/include/system/radio.h
              data->value.int32_array[1] = selector ? RADIO_BAND_FM : RADIO_BAND_AM;
              // For FM set a value in Mhz and for AM set a value in Khz range
              // (channel).
              data->value.int32_array[2] = selector ? 99000000 : 100000;
              // For FM we have a sub-channel and we care about it, for AM pass
              // a dummy value.
              data->value.int32_array[3] = selector ? radio_preset : -1;
              break;
        }

        default:
            // actual implementation will be much complex than this. It should track proper last
            // state. Here just fill with zero.
            memset(&(data->value), 0, sizeof(data->value));
            break;
    }
    printf("getProperty, type 0x%x, time %lld, value_type %d\n", data->prop, data->timestamp,
            data->value_type);
    return 0;
}


static int setProperty(const vehicle_prop_value_t* data) {
    printf("setProperty.");
    // Just print what data will be setting here.
    printf("Setting property %d with value type %d\n", data->prop, data->value_type);
    vehicle_prop_config_t* config = find_config(data->prop);
    if (config == NULL) {
        printf("setProperty: cannot find config 0x%x", data->prop);
        return -EINVAL;
    }
    if (config->value_type != data->value_type) {
        printf("setProperty: type mismatch, passed 0x%x expecting 0x%x", data->value_type,
                config->value_type);
        return -EINVAL;
    }
    if (config->access == VEHICLE_PROP_ACCESS_READ)
    {
        printf("setProperty: permission denied. Property is READONLY\n");
        return -EINVAL;
    }
    switch (data->value_type) {
        case VEHICLE_VALUE_TYPE_FLOAT:
            printf("Value type: FLOAT\nValue: %f\n", data->value.float_value);
            break;
        case VEHICLE_VALUE_TYPE_INT32:
            printf("Value type: INT32\nValue: %d\n", data->value.int32_value);
            break;
        case VEHICLE_VALUE_TYPE_INT64:
            printf("Value type: INT64\nValue: %lld\n", data->value.int64_value);
            break;
        case VEHICLE_VALUE_TYPE_BOOLEAN:
            printf("Value type: BOOLEAN\nValue: %d\n", data->value.boolean_value);
            break;
        case VEHICLE_VALUE_TYPE_STRING:
            printf("Value type: STRING\n Size: %d\n", data->value.str_value.len);
            // NOTE: We only handle ASCII strings here.
            // Print the UTF-8 string.
            char *ascii_out = (char *) malloc ((data->value.str_value.len + 1) * sizeof (char));
            memcpy(ascii_out, data->value.str_value.data, data->value.str_value.len);
            ascii_out[data->value.str_value.len] = '\0';
            printf("Value: %s\n", ascii_out);
            break;
        case VEHICLE_VALUE_TYPE_INT32_VEC4:
            printf("Value type: INT32_VEC4\nValue[0]: %d Value[1] %d Value[2] %d Value[3] %d\n",
                  data->value.int32_array[0], data->value.int32_array[1],
                  data->value.int32_array[2], data->value.int32_array[3]);
            break;
        default:
            printf("Value type not yet handled: %d.\n", data->value_type);
    }
    return 0;
}


int main()
{
    // Get and set make property
    vehicle_prop_value_t makeProperty = {};
    makeProperty.prop = VEHICLE_PROPERTY_INFO_MAKE;

    getProperty(&makeProperty);

    alloc_vehicle_str_from_cstr(BANMA_MAKE, &makeProperty.value.str_value);
    setProperty(&makeProperty);

    // Get and set radio property
    vehicle_prop_value_t radioPresetProperty = {};
    radioPresetProperty.prop = VEHICLE_PROPERTY_RADIO_PRESET;
    radioPresetProperty.value.int32_array[0] = 1;

    getProperty(&radioPresetProperty);

    radioPresetProperty.value.int32_array[1] = 3;
    setProperty(&radioPresetProperty);

    return 0;
}
