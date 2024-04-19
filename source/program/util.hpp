#pragma once
#include "symbols.hpp"

namespace PersonalInfo {
    bool isInGame(u16 species, u16 form) {
        FetchInfo(species, form);
        u8* current_personal_info = read_main<u8*>(static_CurrentPersonalInfo_offset);
        return ((*(current_personal_info + 0x31)) >> 6) & 1;
    }
}

namespace Field {
    template<typename T>
    constexpr u64 getPushOffset() {
        if (std::is_same_v<T, FieldBallItem>) return PushFieldBallItem_offset;
        if (std::is_same_v<T, NestHoleEmitter>) return PushNestHoleEmitter_offset;
        assert(false);
    }
    template<typename T>
    u64 pushFieldObject(const T* flatbuffer) {
        return external<u64>(getPushOffset<T>(), getFieldObjects(), flatbuffer);
    }
    bool checkInheritance(u64 obj, void* inheritance) {
        void* obj_inheritance = external_absolute<void*>(**reinterpret_cast<u64**>(obj + 0x50));
        while (obj_inheritance != nullptr) {
            if (obj_inheritance == inheritance) return true;
            obj_inheritance = *reinterpret_cast<void**>(obj_inheritance);
        }
        return false;
    }
}