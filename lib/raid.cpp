#include "raid.h"
#include "lun.h"

Raid::Raid() {
    Lun lun1;

    luns.push_back(lun1);
}

Raid::~Raid() {
}

bool Raid::is_active() {
    return false;
}

bool Raid::is_onlain() {
    return false;
}
