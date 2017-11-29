/*
 * httpsClient.h
 *
 *  Created on: Oct 4, 2017
 *      Author: knowyou
 */

#ifndef NETWORK_POCOPOSTDATA_HTTPSCLIENT_H_
#define NETWORK_POCOPOSTDATA_HTTPSCLIENT_H_

#include <string>
#include <vector>

struct VersionCheckReqParam
{
    std::string token;
    int     timestamp;
    std::string vin;
    std::string device_sn;
    int     software_type;
    int     package_type;
    std::string hw_part_number;
    std::string hw_version;
    std::string mcu_version;
    std::string app_version;
    std::string os_version;
    std::string backup_os_version;
    std::string emmc_version;
    std::vector<Space_Info> space_info;
};


#endif /* NETWORK_POCOPOSTDATA_HTTPSCLIENT_H_ */
