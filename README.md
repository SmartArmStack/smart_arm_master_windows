# SmartArmMaster for Windows

***Note: Research Only (Noncommercial) License***

Master program used for the [SmartArm](http://doi.org/10.1002/rcs.2053) and related systems. Currently compatible only with the [3DSystems](https://www.3dsystems.com/haptics) device family.
Reads relevant information from the operator-side computer and sends it to the patient-side computer running [ `sas_operator_side_receiver` ](https://github.com/SmartArmStack/smart_arm_stack_researchonly/releases/latest).

## Disclaimer

Use at your own risk, there is no support nor warranty of any kind.

## Quick start

1. Install the device drivers of your 3DSystem device [(Vendor Link)](https://support.3dsystems.com/s/article/Haptic-Device-Drivers-for-OpenHaptics)
2. Configure your device with the `TouchSmartSetup.exe` or similar application. This will name your devices as either `{Left,Right}Device` for two devices, or `Default Device` for one device setups.
3. Install the `SmartArmMaster` application by downloading the latest installer from the release page in this repository.
4. Configure the `configuration.json` file as needed. (More information below)
5. Run the program `SmartArmMaster.exe`. If there are no errors, a GUI similar to the one shown below will appear.

![smart_arm_master_gui_snapshot](https://user-images.githubusercontent.com/46012516/209059707-6195c284-e5e7-4d79-a040-48681675d1e4.png)

## Configuration

Some information for the commonly used fields in `configuration.json`. Variables not listed here should be considered advanced.

| Variable | Meaning |
|-----|-----|
|`left_arm_id` | The label for your left device. Usually `Left Device` in bimanual systems.|
|`right_arm_id` | The label for your right device. Usually `Right Device` in bimanual systems or `Default Device` when only one interface is used.|
|`ps_ip_address`| Patient-side (`ps`) IP, that is, the IP of the computer running the [ `sas_operator_side_receiver` ](https://github.com/SmartArmStack/smart_arm_stack_researchonly/releases/latest).|
|`ps_port`| The port used together with the `ps_id_address`, such as `2222`|
|`os_ip_address`| Operator-side (`os`) IP, that is, the IP of the computer running this program.|
|`clutch_virtual_key_code`| The key which will be used to emulate the clutch, as a Windows [Virtual-Key Code](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) |
|`additional_virtual_key_codes`| A list of additional keys that can be used for arbitrary purposes on the receiving end, as Windows [Virtual-Key Codes](https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes)|
