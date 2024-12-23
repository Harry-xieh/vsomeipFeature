// Copyright (C) 2014-2023 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "../../include/crc/crc.hpp"
#include <iostream>
#include <string>
#include <iomanip>

namespace vsomeip_v3 {

/**
 * Calculates the crc over the provided range.
 *
 * @param begin Constant iterator pointing to begin of the range.
 * @param end Constant iterator pointing to end of the range.
 * @param startValue The crc value from previous call.
 * @return The calculated crc value.
 *
 * Parameters of the CRC:
 * - Width        = 8
 * - Poly         = 0x1D
 * - XorIn        = 0xFF
 * - ReflectIn    = false
 * - XorOut       = 0xFF
 * - ReflectOut   = false
 * - Algorithm    = table-driven
 */
uint8_t e2e_crc::calculate_profile_01(buffer_view _buffer_view, const uint8_t _start_value)
{
    uint8_t crc = _start_value ^ 0xFFU;
    for (uint8_t byte : _buffer_view)
    {
        /*
         * XXX Right-shifting 8 bits on uint8_t results in 0 every time.
         *     It is, quintessentially, shifting all bits into the void.
         */
        crc = static_cast<uint8_t>(
            lookup_table_profile_01_[static_cast<uint8_t>((byte) ^ crc)] /* ^ (crc >> 8U)*/);
    }
    crc = crc ^ 0xFFU;
    return crc;
}

const uint8_t e2e_crc::lookup_table_profile_01_[256] = {
    0x00U, 0x1DU, 0x3AU, 0x27U, 0x74U, 0x69U, 0x4EU, 0x53U, 0xE8U, 0xF5U, 0xD2U, 0xCFU, 0x9CU,
    0x81U, 0xA6U, 0xBBU, 0xCDU, 0xD0U, 0xF7U, 0xEAU, 0xB9U, 0xA4U, 0x83U, 0x9EU, 0x25U, 0x38U,
    0x1FU, 0x02U, 0x51U, 0x4CU, 0x6BU, 0x76U, 0x87U, 0x9AU, 0xBDU, 0xA0U, 0xF3U, 0xEEU, 0xC9U,
    0xD4U, 0x6FU, 0x72U, 0x55U, 0x48U, 0x1BU, 0x06U, 0x21U, 0x3CU, 0x4AU, 0x57U, 0x70U, 0x6DU,
    0x3EU, 0x23U, 0x04U, 0x19U, 0xA2U, 0xBFU, 0x98U, 0x85U, 0xD6U, 0xCBU, 0xECU, 0xF1U, 0x13U,
    0x0EU, 0x29U, 0x34U, 0x67U, 0x7AU, 0x5DU, 0x40U, 0xFBU, 0xE6U, 0xC1U, 0xDCU, 0x8FU, 0x92U,
    0xB5U, 0xA8U, 0xDEU, 0xC3U, 0xE4U, 0xF9U, 0xAAU, 0xB7U, 0x90U, 0x8DU, 0x36U, 0x2BU, 0x0CU,
    0x11U, 0x42U, 0x5FU, 0x78U, 0x65U, 0x94U, 0x89U, 0xAEU, 0xB3U, 0xE0U, 0xFDU, 0xDAU, 0xC7U,
    0x7CU, 0x61U, 0x46U, 0x5BU, 0x08U, 0x15U, 0x32U, 0x2FU, 0x59U, 0x44U, 0x63U, 0x7EU, 0x2DU,
    0x30U, 0x17U, 0x0AU, 0xB1U, 0xACU, 0x8BU, 0x96U, 0xC5U, 0xD8U, 0xFFU, 0xE2U, 0x26U, 0x3BU,
    0x1CU, 0x01U, 0x52U, 0x4FU, 0x68U, 0x75U, 0xCEU, 0xD3U, 0xF4U, 0xE9U, 0xBAU, 0xA7U, 0x80U,
    0x9DU, 0xEBU, 0xF6U, 0xD1U, 0xCCU, 0x9FU, 0x82U, 0xA5U, 0xB8U, 0x03U, 0x1EU, 0x39U, 0x24U,
    0x77U, 0x6AU, 0x4DU, 0x50U, 0xA1U, 0xBCU, 0x9BU, 0x86U, 0xD5U, 0xC8U, 0xEFU, 0xF2U, 0x49U,
    0x54U, 0x73U, 0x6EU, 0x3DU, 0x20U, 0x07U, 0x1AU, 0x6CU, 0x71U, 0x56U, 0x4BU, 0x18U, 0x05U,
    0x22U, 0x3FU, 0x84U, 0x99U, 0xBEU, 0xA3U, 0xF0U, 0xEDU, 0xCAU, 0xD7U, 0x35U, 0x28U, 0x0FU,
    0x12U, 0x41U, 0x5CU, 0x7BU, 0x66U, 0xDDU, 0xC0U, 0xE7U, 0xFAU, 0xA9U, 0xB4U, 0x93U, 0x8EU,
    0xF8U, 0xE5U, 0xC2U, 0xDFU, 0x8CU, 0x91U, 0xB6U, 0xABU, 0x10U, 0x0DU, 0x2AU, 0x37U, 0x64U,
    0x79U, 0x5EU, 0x43U, 0xB2U, 0xAFU, 0x88U, 0x95U, 0xC6U, 0xDBU, 0xFCU, 0xE1U, 0x5AU, 0x47U,
    0x60U, 0x7DU, 0x2EU, 0x33U, 0x14U, 0x09U, 0x7FU, 0x62U, 0x45U, 0x58U, 0x0BU, 0x16U, 0x31U,
    0x2CU, 0x97U, 0x8AU, 0xADU, 0xB0U, 0xE3U, 0xFEU, 0xD9U, 0xC4U};

/**
 * Calculates the CRC over the provided range.
 *
 * @param begin Constant iterator pointing to begin of the range.
 * @param end Constant iterator pointing to end of the range.
 * @param startValue The CRC value from previous call.
 * @return The calculated CRC value.
 *
 * Parameters of the CRC:
 * - Width        = 32
 * - Poly         = 0xF4ACFB13
 * - XorIn        = 0xFFFFFFFF
 * - ReflectIn    = true
 * - XorOut       = 0xFFFFFFFF
 * - ReflectOut   = true
 */
uint32_t e2e_crc::calculate_profile_04(buffer_view _buffer_view, const uint32_t _start_value)
{
    uint32_t crc = (_start_value ^ 0xFFFFFFFFU);

    for (uint8_t byte : _buffer_view)
        crc = lookup_table_profile_04_[static_cast<uint8_t>(byte ^ crc)] ^ (crc >> 8U);

    return (crc ^ 0xFFFFFFFFU);
}

const uint32_t e2e_crc::lookup_table_profile_04_[256] = {
    0x00000000U, 0x30850FF5U, 0x610A1FEAU, 0x518F101FU, 0xC2143FD4U, 0xF2913021U, 0xA31E203EU,
    0x939B2FCBU, 0x159615F7U, 0x25131A02U, 0x749C0A1DU, 0x441905E8U, 0xD7822A23U, 0xE70725D6U,
    0xB68835C9U, 0x860D3A3CU, 0x2B2C2BEEU, 0x1BA9241BU, 0x4A263404U, 0x7AA33BF1U, 0xE938143AU,
    0xD9BD1BCFU, 0x88320BD0U, 0xB8B70425U, 0x3EBA3E19U, 0x0E3F31ECU, 0x5FB021F3U, 0x6F352E06U,
    0xFCAE01CDU, 0xCC2B0E38U, 0x9DA41E27U, 0xAD2111D2U, 0x565857DCU, 0x66DD5829U, 0x37524836U,
    0x07D747C3U, 0x944C6808U, 0xA4C967FDU, 0xF54677E2U, 0xC5C37817U, 0x43CE422BU, 0x734B4DDEU,
    0x22C45DC1U, 0x12415234U, 0x81DA7DFFU, 0xB15F720AU, 0xE0D06215U, 0xD0556DE0U, 0x7D747C32U,
    0x4DF173C7U, 0x1C7E63D8U, 0x2CFB6C2DU, 0xBF6043E6U, 0x8FE54C13U, 0xDE6A5C0CU, 0xEEEF53F9U,
    0x68E269C5U, 0x58676630U, 0x09E8762FU, 0x396D79DAU, 0xAAF65611U, 0x9A7359E4U, 0xCBFC49FBU,
    0xFB79460EU, 0xACB0AFB8U, 0x9C35A04DU, 0xCDBAB052U, 0xFD3FBFA7U, 0x6EA4906CU, 0x5E219F99U,
    0x0FAE8F86U, 0x3F2B8073U, 0xB926BA4FU, 0x89A3B5BAU, 0xD82CA5A5U, 0xE8A9AA50U, 0x7B32859BU,
    0x4BB78A6EU, 0x1A389A71U, 0x2ABD9584U, 0x879C8456U, 0xB7198BA3U, 0xE6969BBCU, 0xD6139449U,
    0x4588BB82U, 0x750DB477U, 0x2482A468U, 0x1407AB9DU, 0x920A91A1U, 0xA28F9E54U, 0xF3008E4BU,
    0xC38581BEU, 0x501EAE75U, 0x609BA180U, 0x3114B19FU, 0x0191BE6AU, 0xFAE8F864U, 0xCA6DF791U,
    0x9BE2E78EU, 0xAB67E87BU, 0x38FCC7B0U, 0x0879C845U, 0x59F6D85AU, 0x6973D7AFU, 0xEF7EED93U,
    0xDFFBE266U, 0x8E74F279U, 0xBEF1FD8CU, 0x2D6AD247U, 0x1DEFDDB2U, 0x4C60CDADU, 0x7CE5C258U,
    0xD1C4D38AU, 0xE141DC7FU, 0xB0CECC60U, 0x804BC395U, 0x13D0EC5EU, 0x2355E3ABU, 0x72DAF3B4U,
    0x425FFC41U, 0xC452C67DU, 0xF4D7C988U, 0xA558D997U, 0x95DDD662U, 0x0646F9A9U, 0x36C3F65CU,
    0x674CE643U, 0x57C9E9B6U, 0xC8DF352FU, 0xF85A3ADAU, 0xA9D52AC5U, 0x99502530U, 0x0ACB0AFBU,
    0x3A4E050EU, 0x6BC11511U, 0x5B441AE4U, 0xDD4920D8U, 0xEDCC2F2DU, 0xBC433F32U, 0x8CC630C7U,
    0x1F5D1F0CU, 0x2FD810F9U, 0x7E5700E6U, 0x4ED20F13U, 0xE3F31EC1U, 0xD3761134U, 0x82F9012BU,
    0xB27C0EDEU, 0x21E72115U, 0x11622EE0U, 0x40ED3EFFU, 0x7068310AU, 0xF6650B36U, 0xC6E004C3U,
    0x976F14DCU, 0xA7EA1B29U, 0x347134E2U, 0x04F43B17U, 0x557B2B08U, 0x65FE24FDU, 0x9E8762F3U,
    0xAE026D06U, 0xFF8D7D19U, 0xCF0872ECU, 0x5C935D27U, 0x6C1652D2U, 0x3D9942CDU, 0x0D1C4D38U,
    0x8B117704U, 0xBB9478F1U, 0xEA1B68EEU, 0xDA9E671BU, 0x490548D0U, 0x79804725U, 0x280F573AU,
    0x188A58CFU, 0xB5AB491DU, 0x852E46E8U, 0xD4A156F7U, 0xE4245902U, 0x77BF76C9U, 0x473A793CU,
    0x16B56923U, 0x263066D6U, 0xA03D5CEAU, 0x90B8531FU, 0xC1374300U, 0xF1B24CF5U, 0x6229633EU,
    0x52AC6CCBU, 0x03237CD4U, 0x33A67321U, 0x646F9A97U, 0x54EA9562U, 0x0565857DU, 0x35E08A88U,
    0xA67BA543U, 0x96FEAAB6U, 0xC771BAA9U, 0xF7F4B55CU, 0x71F98F60U, 0x417C8095U, 0x10F3908AU,
    0x20769F7FU, 0xB3EDB0B4U, 0x8368BF41U, 0xD2E7AF5EU, 0xE262A0ABU, 0x4F43B179U, 0x7FC6BE8CU,
    0x2E49AE93U, 0x1ECCA166U, 0x8D578EADU, 0xBDD28158U, 0xEC5D9147U, 0xDCD89EB2U, 0x5AD5A48EU,
    0x6A50AB7BU, 0x3BDFBB64U, 0x0B5AB491U, 0x98C19B5AU, 0xA84494AFU, 0xF9CB84B0U, 0xC94E8B45U,
    0x3237CD4BU, 0x02B2C2BEU, 0x533DD2A1U, 0x63B8DD54U, 0xF023F29FU, 0xC0A6FD6AU, 0x9129ED75U,
    0xA1ACE280U, 0x27A1D8BCU, 0x1724D749U, 0x46ABC756U, 0x762EC8A3U, 0xE5B5E768U, 0xD530E89DU,
    0x84BFF882U, 0xB43AF777U, 0x191BE6A5U, 0x299EE950U, 0x7811F94FU, 0x4894F6BAU, 0xDB0FD971U,
    0xEB8AD684U, 0xBA05C69BU, 0x8A80C96EU, 0x0C8DF352U, 0x3C08FCA7U, 0x6D87ECB8U, 0x5D02E34DU,
    0xCE99CC86U, 0xFE1CC373U, 0xAF93D36CU, 0x9F16DC99U};

/**
 * Calculates the CRC16 over the provided range.
 */
uint16_t e2e_crc::calculate_profile_05(buffer_view _buffer_view, const uint16_t _start_value)
{
    const uint8_t* buffer        = _buffer_view.begin();
    uint32_t       buffer_length = (uint32_t)_buffer_view.data_length();
    uint16_t       crc           = _start_value;

    /* Process all data (byte wise) */
    for (uint32_t i = 0; i < buffer_length; ++i)
    {
        /* Process one byte of data */
        crc =
            lookup_table_profile_05_[((uint8_t)(crc >> 8U)) ^ buffer[i]] ^ ((uint16_t)(crc << 8U));
    }

    /* Specified final XOR value for CRC16 is 0, no need to actually xor anything here */
    return crc;
}

const uint16_t e2e_crc::lookup_table_profile_05_[256] = {
    0x0000U, 0x1021U, 0x2042U, 0x3063U, 0x4084U, 0x50A5U, 0x60C6U, 0x70E7U, 0x8108U, 0x9129U,
    0xA14AU, 0xB16BU, 0xC18CU, 0xD1ADU, 0xE1CEU, 0xF1EFU, 0x1231U, 0x0210U, 0x3273U, 0x2252U,
    0x52B5U, 0x4294U, 0x72F7U, 0x62D6U, 0x9339U, 0x8318U, 0xB37BU, 0xA35AU, 0xD3BDU, 0xC39CU,
    0xF3FFU, 0xE3DEU, 0x2462U, 0x3443U, 0x0420U, 0x1401U, 0x64E6U, 0x74C7U, 0x44A4U, 0x5485U,
    0xA56AU, 0xB54BU, 0x8528U, 0x9509U, 0xE5EEU, 0xF5CFU, 0xC5ACU, 0xD58DU, 0x3653U, 0x2672U,
    0x1611U, 0x0630U, 0x76D7U, 0x66F6U, 0x5695U, 0x46B4U, 0xB75BU, 0xA77AU, 0x9719U, 0x8738U,
    0xF7DFU, 0xE7FEU, 0xD79DU, 0xC7BCU, 0x48C4U, 0x58E5U, 0x6886U, 0x78A7U, 0x0840U, 0x1861U,
    0x2802U, 0x3823U, 0xC9CCU, 0xD9EDU, 0xE98EU, 0xF9AFU, 0x8948U, 0x9969U, 0xA90AU, 0xB92BU,
    0x5AF5U, 0x4AD4U, 0x7AB7U, 0x6A96U, 0x1A71U, 0x0A50U, 0x3A33U, 0x2A12U, 0xDBFDU, 0xCBDCU,
    0xFBBFU, 0xEB9EU, 0x9B79U, 0x8B58U, 0xBB3BU, 0xAB1AU, 0x6CA6U, 0x7C87U, 0x4CE4U, 0x5CC5U,
    0x2C22U, 0x3C03U, 0x0C60U, 0x1C41U, 0xEDAEU, 0xFD8FU, 0xCDECU, 0xDDCDU, 0xAD2AU, 0xBD0BU,
    0x8D68U, 0x9D49U, 0x7E97U, 0x6EB6U, 0x5ED5U, 0x4EF4U, 0x3E13U, 0x2E32U, 0x1E51U, 0x0E70U,
    0xFF9FU, 0xEFBEU, 0xDFDDU, 0xCFFCU, 0xBF1BU, 0xAF3AU, 0x9F59U, 0x8F78U, 0x9188U, 0x81A9U,
    0xB1CAU, 0xA1EBU, 0xD10CU, 0xC12DU, 0xF14EU, 0xE16FU, 0x1080U, 0x00A1U, 0x30C2U, 0x20E3U,
    0x5004U, 0x4025U, 0x7046U, 0x6067U, 0x83B9U, 0x9398U, 0xA3FBU, 0xB3DAU, 0xC33DU, 0xD31CU,
    0xE37FU, 0xF35EU, 0x02B1U, 0x1290U, 0x22F3U, 0x32D2U, 0x4235U, 0x5214U, 0x6277U, 0x7256U,
    0xB5EAU, 0xA5CBU, 0x95A8U, 0x8589U, 0xF56EU, 0xE54FU, 0xD52CU, 0xC50DU, 0x34E2U, 0x24C3U,
    0x14A0U, 0x0481U, 0x7466U, 0x6447U, 0x5424U, 0x4405U, 0xA7DBU, 0xB7FAU, 0x8799U, 0x97B8U,
    0xE75FU, 0xF77EU, 0xC71DU, 0xD73CU, 0x26D3U, 0x36F2U, 0x0691U, 0x16B0U, 0x6657U, 0x7676U,
    0x4615U, 0x5634U, 0xD94CU, 0xC96DU, 0xF90EU, 0xE92FU, 0x99C8U, 0x89E9U, 0xB98AU, 0xA9ABU,
    0x5844U, 0x4865U, 0x7806U, 0x6827U, 0x18C0U, 0x08E1U, 0x3882U, 0x28A3U, 0xCB7DU, 0xDB5CU,
    0xEB3FU, 0xFB1EU, 0x8BF9U, 0x9BD8U, 0xABBBU, 0xBB9AU, 0x4A75U, 0x5A54U, 0x6A37U, 0x7A16U,
    0x0AF1U, 0x1AD0U, 0x2AB3U, 0x3A92U, 0xFD2EU, 0xED0FU, 0xDD6CU, 0xCD4DU, 0xBDAAU, 0xAD8BU,
    0x9DE8U, 0x8DC9U, 0x7C26U, 0x6C07U, 0x5C64U, 0x4C45U, 0x3CA2U, 0x2C83U, 0x1CE0U, 0x0CC1U,
    0xEF1FU, 0xFF3EU, 0xCF5DU, 0xDF7CU, 0xAF9BU, 0xBFBAU, 0x8FD9U, 0x9FF8U, 0x6E17U, 0x7E36U,
    0x4E55U, 0x5E74U, 0x2E93U, 0x3EB2U, 0x0ED1U, 0x1EF0U};

/**
 * Calculates the CRC over the provided range.
 *
 * @param begin Constant iterator pointing to begin of the range.
 * @param end Constant iterator pointing to end of the range.
 * @param startValue The CRC value from previous call.
 * @return The calculated CRC value.
 *
 * Parameters of the CRC:
 * - Width        = 32
 * - Poly         = 0x4C11DB7
 * - InitValue    = 0xFFFFFFFF
 * - ReflectIn    = true
 * - XorOut       = 0xFFFFFFFF
 * - ReflectOut   = true
 */
uint32_t e2e_crc::calculate_profile_custom(buffer_view _buffer_view)
{
    // InitValue
    uint32_t crc = 0xFFFFFFFFU;

    for (uint8_t byte : _buffer_view)
    {
        crc = lookup_table_profile_custom_[static_cast<uint8_t>(byte ^ crc)] ^ (crc >> 8U);
    }

    // XorOut
    crc = crc ^ 0xFFFFFFFFU;
    return crc;
}

const uint32_t e2e_crc::lookup_table_profile_custom_[256] = {
    0x00000000U, 0x77073096U, 0xEE0E612CU, 0x990951BAU, 0x076DC419U, 0x706AF48FU, 0xE963A535U,
    0x9E6495A3U, 0x0EDB8832U, 0x79DCB8A4U, 0xE0D5E91EU, 0x97D2D988U, 0x09B64C2BU, 0x7EB17CBDU,
    0xE7B82D07U, 0x90BF1D91U, 0x1DB71064U, 0x6AB020F2U, 0xF3B97148U, 0x84BE41DEU, 0x1ADAD47DU,
    0x6DDDE4EBU, 0xF4D4B551U, 0x83D385C7U, 0x136C9856U, 0x646BA8C0U, 0xFD62F97AU, 0x8A65C9ECU,
    0x14015C4FU, 0x63066CD9U, 0xFA0F3D63U, 0x8D080DF5U, 0x3B6E20C8U, 0x4C69105EU, 0xD56041E4U,
    0xA2677172U, 0x3C03E4D1U, 0x4B04D447U, 0xD20D85FDU, 0xA50AB56BU, 0x35B5A8FAU, 0x42B2986CU,
    0xDBBBC9D6U, 0xACBCF940U, 0x32D86CE3U, 0x45DF5C75U, 0xDCD60DCFU, 0xABD13D59U, 0x26D930ACU,
    0x51DE003AU, 0xC8D75180U, 0xBFD06116U, 0x21B4F4B5U, 0x56B3C423U, 0xCFBA9599U, 0xB8BDA50FU,
    0x2802B89EU, 0x5F058808U, 0xC60CD9B2U, 0xB10BE924U, 0x2F6F7C87U, 0x58684C11U, 0xC1611DABU,
    0xB6662D3DU, 0x76DC4190U, 0x01DB7106U, 0x98D220BCU, 0xEFD5102AU, 0x71B18589U, 0x06B6B51FU,
    0x9FBFE4A5U, 0xE8B8D433U, 0x7807C9A2U, 0x0F00F934U, 0x9609A88EU, 0xE10E9818U, 0x7F6A0DBBU,
    0x086D3D2DU, 0x91646C97U, 0xE6635C01U, 0x6B6B51F4U, 0x1C6C6162U, 0x856530D8U, 0xF262004EU,
    0x6C0695EDU, 0x1B01A57BU, 0x8208F4C1U, 0xF50FC457U, 0x65B0D9C6U, 0x12B7E950U, 0x8BBEB8EAU,
    0xFCB9887CU, 0x62DD1DDFU, 0x15DA2D49U, 0x8CD37CF3U, 0xFBD44C65U, 0x4DB26158U, 0x3AB551CEU,
    0xA3BC0074U, 0xD4BB30E2U, 0x4ADFA541U, 0x3DD895D7U, 0xA4D1C46DU, 0xD3D6F4FBU, 0x4369E96AU,
    0x346ED9FCU, 0xAD678846U, 0xDA60B8D0U, 0x44042D73U, 0x33031DE5U, 0xAA0A4C5FU, 0xDD0D7CC9U,
    0x5005713CU, 0x270241AAU, 0xBE0B1010U, 0xC90C2086U, 0x5768B525U, 0x206F85B3U, 0xB966D409U,
    0xCE61E49FU, 0x5EDEF90EU, 0x29D9C998U, 0xB0D09822U, 0xC7D7A8B4U, 0x59B33D17U, 0x2EB40D81U,
    0xB7BD5C3BU, 0xC0BA6CADU, 0xEDB88320U, 0x9ABFB3B6U, 0x03B6E20CU, 0x74B1D29AU, 0xEAD54739U,
    0x9DD277AFU, 0x04DB2615U, 0x73DC1683U, 0xE3630B12U, 0x94643B84U, 0x0D6D6A3EU, 0x7A6A5AA8U,
    0xE40ECF0BU, 0x9309FF9DU, 0x0A00AE27U, 0x7D079EB1U, 0xF00F9344U, 0x8708A3D2U, 0x1E01F268U,
    0x6906C2FEU, 0xF762575DU, 0x806567CBU, 0x196C3671U, 0x6E6B06E7U, 0xFED41B76U, 0x89D32BE0U,
    0x10DA7A5AU, 0x67DD4ACCU, 0xF9B9DF6FU, 0x8EBEEFF9U, 0x17B7BE43U, 0x60B08ED5U, 0xD6D6A3E8U,
    0xA1D1937EU, 0x38D8C2C4U, 0x4FDFF252U, 0xD1BB67F1U, 0xA6BC5767U, 0x3FB506DDU, 0x48B2364BU,
    0xD80D2BDAU, 0xAF0A1B4CU, 0x36034AF6U, 0x41047A60U, 0xDF60EFC3U, 0xA867DF55U, 0x316E8EEFU,
    0x4669BE79U, 0xCB61B38CU, 0xBC66831AU, 0x256FD2A0U, 0x5268E236U, 0xCC0C7795U, 0xBB0B4703U,
    0x220216B9U, 0x5505262FU, 0xC5BA3BBEU, 0xB2BD0B28U, 0x2BB45A92U, 0x5CB36A04U, 0xC2D7FFA7U,
    0xB5D0CF31U, 0x2CD99E8BU, 0x5BDEAE1DU, 0x9B64C2B0U, 0xEC63F226U, 0x756AA39CU, 0x026D930AU,
    0x9C0906A9U, 0xEB0E363FU, 0x72076785U, 0x05005713U, 0x95BF4A82U, 0xE2B87A14U, 0x7BB12BAEU,
    0x0CB61B38U, 0x92D28E9BU, 0xE5D5BE0DU, 0x7CDCEFB7U, 0x0BDBDF21U, 0x86D3D2D4U, 0xF1D4E242U,
    0x68DDB3F8U, 0x1FDA836EU, 0x81BE16CDU, 0xF6B9265BU, 0x6FB077E1U, 0x18B74777U, 0x88085AE6U,
    0xFF0F6A70U, 0x66063BCAU, 0x11010B5CU, 0x8F659EFFU, 0xF862AE69U, 0x616BFFD3U, 0x166CCF45U,
    0xA00AE278U, 0xD70DD2EEU, 0x4E048354U, 0x3903B3C2U, 0xA7672661U, 0xD06016F7U, 0x4969474DU,
    0x3E6E77DBU, 0xAED16A4AU, 0xD9D65ADCU, 0x40DF0B66U, 0x37D83BF0U, 0xA9BCAE53U, 0xDEBB9EC5U,
    0x47B2CF7FU, 0x30B5FFE9U, 0xBDBDF21CU, 0xCABAC28AU, 0x53B39330U, 0x24B4A3A6U, 0xBAD03605U,
    0xCDD70693U, 0x54DE5729U, 0x23D967BFU, 0xB3667A2EU, 0xC4614AB8U, 0x5D681B02U, 0x2A6F2B94U,
    0xB40BBE37U, 0xC30C8EA1U, 0x5A05DF1BU, 0x2D02EF8DU};

/**
 * Calculates the CRC over the provided range.
 *
 * @param begin Constant iterator pointing to begin of the range.
 * @param end Constant iterator pointing to end of the range.
 * @param startValue The CRC value from previous call.
 * @return The calculated CRC value.
 *
 * Parameters of the CRC:
 * - Width        = 64
 * - Poly         = 0x42F0E1EBA9EA3693
 * - XorIn        = 0xFFFFFFFFFFFFFFFF
 * - ReflectIn    = true
 * - XorOut       = 0xFFFFFFFFFFFFFFFF
 * - ReflectOut   = true
 */
uint64_t e2e_crc::calculate_profile_07(buffer_view _buffer_view, const uint64_t _start_value)
{
    uint64_t crc = (_start_value ^ 0xFFFFFFFFFFFFFFFFU);

    for (uint8_t byte : _buffer_view)
        crc = lookup_table_profile_07_[static_cast<uint8_t>(byte ^ crc)] ^ (crc >> 8U);

    return (crc ^ 0xFFFFFFFFFFFFFFFFU);
}

const uint64_t e2e_crc::lookup_table_profile_07_[256] = {
    0x0000000000000000, 0xB32E4CBE03A75F6F, 0xF4843657A840A05B, 0x47AA7AE9ABE7FF34,
    0x7BD0C384FF8F5E33, 0xC8FE8F3AFC28015C, 0x8F54F5D357CFFE68, 0x3C7AB96D5468A107,
    0xF7A18709FF1EBC66, 0x448FCBB7FCB9E309, 0x0325B15E575E1C3D, 0xB00BFDE054F94352,
    0x8C71448D0091E255, 0x3F5F08330336BD3A, 0x78F572DAA8D1420E, 0xCBDB3E64AB761D61,
    0x7D9BA13851336649, 0xCEB5ED8652943926, 0x891F976FF973C612, 0x3A31DBD1FAD4997D,
    0x064B62BCAEBC387A, 0xB5652E02AD1B6715, 0xF2CF54EB06FC9821, 0x41E11855055BC74E,
    0x8A3A2631AE2DDA2F, 0x39146A8FAD8A8540, 0x7EBE1066066D7A74, 0xCD905CD805CA251B,
    0xF1EAE5B551A2841C, 0x42C4A90B5205DB73, 0x056ED3E2F9E22447, 0xB6409F5CFA457B28,
    0xFB374270A266CC92, 0x48190ECEA1C193FD, 0x0FB374270A266CC9, 0xBC9D3899098133A6,
    0x80E781F45DE992A1, 0x33C9CD4A5E4ECDCE, 0x7463B7A3F5A932FA, 0xC74DFB1DF60E6D95,
    0x0C96C5795D7870F4, 0xBFB889C75EDF2F9B, 0xF812F32EF538D0AF, 0x4B3CBF90F69F8FC0,
    0x774606FDA2F72EC7, 0xC4684A43A15071A8, 0x83C230AA0AB78E9C, 0x30EC7C140910D1F3,
    0x86ACE348F355AADB, 0x3582AFF6F0F2F5B4, 0x7228D51F5B150A80, 0xC10699A158B255EF,
    0xFD7C20CC0CDAF4E8, 0x4E526C720F7DAB87, 0x09F8169BA49A54B3, 0xBAD65A25A73D0BDC,
    0x710D64410C4B16BD, 0xC22328FF0FEC49D2, 0x85895216A40BB6E6, 0x36A71EA8A7ACE989,
    0x0ADDA7C5F3C4488E, 0xB9F3EB7BF06317E1, 0xFE5991925B84E8D5, 0x4D77DD2C5823B7BA,
    0x64B62BCAEBC387A1, 0xD7986774E864D8CE, 0x90321D9D438327FA, 0x231C512340247895,
    0x1F66E84E144CD992, 0xAC48A4F017EB86FD, 0xEBE2DE19BC0C79C9, 0x58CC92A7BFAB26A6,
    0x9317ACC314DD3BC7, 0x2039E07D177A64A8, 0x67939A94BC9D9B9C, 0xD4BDD62ABF3AC4F3,
    0xE8C76F47EB5265F4, 0x5BE923F9E8F53A9B, 0x1C4359104312C5AF, 0xAF6D15AE40B59AC0,
    0x192D8AF2BAF0E1E8, 0xAA03C64CB957BE87, 0xEDA9BCA512B041B3, 0x5E87F01B11171EDC,
    0x62FD4976457FBFDB, 0xD1D305C846D8E0B4, 0x96797F21ED3F1F80, 0x2557339FEE9840EF,
    0xEE8C0DFB45EE5D8E, 0x5DA24145464902E1, 0x1A083BACEDAEFDD5, 0xA9267712EE09A2BA,
    0x955CCE7FBA6103BD, 0x267282C1B9C65CD2, 0x61D8F8281221A3E6, 0xD2F6B4961186FC89,
    0x9F8169BA49A54B33, 0x2CAF25044A02145C, 0x6B055FEDE1E5EB68, 0xD82B1353E242B407,
    0xE451AA3EB62A1500, 0x577FE680B58D4A6F, 0x10D59C691E6AB55B, 0xA3FBD0D71DCDEA34,
    0x6820EEB3B6BBF755, 0xDB0EA20DB51CA83A, 0x9CA4D8E41EFB570E, 0x2F8A945A1D5C0861,
    0x13F02D374934A966, 0xA0DE61894A93F609, 0xE7741B60E174093D, 0x545A57DEE2D35652,
    0xE21AC88218962D7A, 0x5134843C1B317215, 0x169EFED5B0D68D21, 0xA5B0B26BB371D24E,
    0x99CA0B06E7197349, 0x2AE447B8E4BE2C26, 0x6D4E3D514F59D312, 0xDE6071EF4CFE8C7D,
    0x15BB4F8BE788911C, 0xA6950335E42FCE73, 0xE13F79DC4FC83147, 0x521135624C6F6E28,
    0x6E6B8C0F1807CF2F, 0xDD45C0B11BA09040, 0x9AEFBA58B0476F74, 0x29C1F6E6B3E0301B,
    0xC96C5795D7870F42, 0x7A421B2BD420502D, 0x3DE861C27FC7AF19, 0x8EC62D7C7C60F076,
    0xB2BC941128085171, 0x0192D8AF2BAF0E1E, 0x4638A2468048F12A, 0xF516EEF883EFAE45,
    0x3ECDD09C2899B324, 0x8DE39C222B3EEC4B, 0xCA49E6CB80D9137F, 0x7967AA75837E4C10,
    0x451D1318D716ED17, 0xF6335FA6D4B1B278, 0xB199254F7F564D4C, 0x02B769F17CF11223,
    0xB4F7F6AD86B4690B, 0x07D9BA1385133664, 0x4073C0FA2EF4C950, 0xF35D8C442D53963F,
    0xCF273529793B3738, 0x7C0979977A9C6857, 0x3BA3037ED17B9763, 0x888D4FC0D2DCC80C,
    0x435671A479AAD56D, 0xF0783D1A7A0D8A02, 0xB7D247F3D1EA7536, 0x04FC0B4DD24D2A59,
    0x3886B22086258B5E, 0x8BA8FE9E8582D431, 0xCC0284772E652B05, 0x7F2CC8C92DC2746A,
    0x325B15E575E1C3D0, 0x8175595B76469CBF, 0xC6DF23B2DDA1638B, 0x75F16F0CDE063CE4,
    0x498BD6618A6E9DE3, 0xFAA59ADF89C9C28C, 0xBD0FE036222E3DB8, 0x0E21AC88218962D7,
    0xC5FA92EC8AFF7FB6, 0x76D4DE52895820D9, 0x317EA4BB22BFDFED, 0x8250E80521188082,
    0xBE2A516875702185, 0x0D041DD676D77EEA, 0x4AAE673FDD3081DE, 0xF9802B81DE97DEB1,
    0x4FC0B4DD24D2A599, 0xFCEEF8632775FAF6, 0xBB44828A8C9205C2, 0x086ACE348F355AAD,
    0x34107759DB5DFBAA, 0x873E3BE7D8FAA4C5, 0xC094410E731D5BF1, 0x73BA0DB070BA049E,
    0xB86133D4DBCC19FF, 0x0B4F7F6AD86B4690, 0x4CE50583738CB9A4, 0xFFCB493D702BE6CB,
    0xC3B1F050244347CC, 0x709FBCEE27E418A3, 0x3735C6078C03E797, 0x841B8AB98FA4B8F8,
    0xADDA7C5F3C4488E3, 0x1EF430E13FE3D78C, 0x595E4A08940428B8, 0xEA7006B697A377D7,
    0xD60ABFDBC3CBD6D0, 0x6524F365C06C89BF, 0x228E898C6B8B768B, 0x91A0C532682C29E4,
    0x5A7BFB56C35A3485, 0xE955B7E8C0FD6BEA, 0xAEFFCD016B1A94DE, 0x1DD181BF68BDCBB1,
    0x21AB38D23CD56AB6, 0x9285746C3F7235D9, 0xD52F0E859495CAED, 0x6601423B97329582,
    0xD041DD676D77EEAA, 0x636F91D96ED0B1C5, 0x24C5EB30C5374EF1, 0x97EBA78EC690119E,
    0xAB911EE392F8B099, 0x18BF525D915FEFF6, 0x5F1528B43AB810C2, 0xEC3B640A391F4FAD,
    0x27E05A6E926952CC, 0x94CE16D091CE0DA3, 0xD3646C393A29F297, 0x604A2087398EADF8,
    0x5C3099EA6DE60CFF, 0xEF1ED5546E415390, 0xA8B4AFBDC5A6ACA4, 0x1B9AE303C601F3CB,
    0x56ED3E2F9E224471, 0xE5C372919D851B1E, 0xA26908783662E42A, 0x114744C635C5BB45,
    0x2D3DFDAB61AD1A42, 0x9E13B115620A452D, 0xD9B9CBFCC9EDBA19, 0x6A978742CA4AE576,
    0xA14CB926613CF817, 0x1262F598629BA778, 0x55C88F71C97C584C, 0xE6E6C3CFCADB0723,
    0xDA9C7AA29EB3A624, 0x69B2361C9D14F94B, 0x2E184CF536F3067F, 0x9D36004B35545910,
    0x2B769F17CF112238, 0x9858D3A9CCB67D57, 0xDFF2A94067518263, 0x6CDCE5FE64F6DD0C,
    0x50A65C93309E7C0B, 0xE388102D33392364, 0xA4226AC498DEDC50, 0x170C267A9B79833F,
    0xDCD7181E300F9E5E, 0x6FF954A033A8C131, 0x28532E49984F3E05, 0x9B7D62F79BE8616A,
    0xA707DB9ACF80C06D, 0x14299724CC279F02, 0x5383EDCD67C06036, 0xE0ADA17364673F59};

} // namespace vsomeip_v3
