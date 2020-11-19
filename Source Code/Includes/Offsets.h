//
// Created by harak on 2020-07-28.
//

#ifndef DARK_FORCE_OFFSETS_H
#define DARK_FORCE_OFFSETS_H

#endif //DARK_FORCE_OFFSETS_H

namespace Offsets {
    enum Offsets {
        SpeedHackDetector = 0xF60FB4, //SpeedHackDetector:private void Update
        Dual = 0x26CC774, //public bool get_IsDual:WeaponDatas
        AutoReload = 0x26CFF4C, //public bool IsAutoReload
        recoil = 0x26CFF44, //public bool IsRecoil:WeaponDatas
        Firerate = 0x26CE294, //public float FireRatePoint:WeaponDatas
        Firerate2 = 0x26CEFD8, //public int FireRatePointAdded
        playername = 0x113F8D8, //public string name:PhotonPlayer
        CurrentInAmmo = 0x26CF190, //public int ClipPointAdded
        CurrentInAmmo2 = 0x26CE494, //public float ClipPoint:WeaponDatas
        Store = 0x26D37B0, //public bool IsShowStore:WeaponDatas
        AccuracyPoint = 0x26CE394, //public float AccuracyPoint:WeaponDatas
        AccuracyPointAdded = 0x26CF0B4, //public int AccuracyPointAdded
        ReloadTimePoint = 0x26CE67C, //public float ReloadTimePoint:WeaponDatas
        ReloadTimePointAdded = 0x26CF26C, //public int ReloadTimePointAdded
        AttackRangePoint = 0x26CE964, //public float AttackRangePoint:WeaponDatas
        AttackRangePointAdded = 0x26CF5DC, //public int AttackRangePointAdded
        ExplosionRangePoint = 0x26CE594, //public float ExplosionRangePoint:WeaponDatas
        CanAim = 0x26C9954, //public bool CanAim:WeaponDatas
        /*heath = 0xFFFFFFF,*/
        Mine = 0x287DF8C, //public bool IsMine:NetworkCharacter
        DeathNum = 0x2882E64, //public int GetDeathNum:NetworkCharacter
        KilledNum = 0x2882BC0 //public int GetKilledNum:NetworkCharacter
    };
}