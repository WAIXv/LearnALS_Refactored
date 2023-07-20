# UE新手入坟笔记



## UE中的对象指针



### TObjectPtr<>

````c++
TObjectPtr<UAlsCameraSettings> Settings;

TObjectPtr<ACharacter> Character;

TWeakObjectPtr<UAnimInstance> AnimationInstance;
````

在项目代码中经常看到很多类成员并非直接使用UObject*裸指针，而是使用TObjectPtr<ClassName>

原因是UE5放弃了对32位系统的支持，从而只考虑64位的指针，而寻址空间不可能将指针的64位全部用完。因此，这64位就可以用来储存额外的信息，不过据说是用来反射Debug，不懂





