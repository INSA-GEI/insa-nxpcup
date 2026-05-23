function update_supportpackage()
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% The MW_Camera.cpp ,MW_DC_Motor.cpp, MW_Servo.cpp and MW_Camera.h
% are copied into a back of folder "backup" in the path  
% Support_packageRootDirectory\toolbox\target\supportpackages\freedomboard                                                                           
% The updated files are then copied into the respective location                                                                              
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

Support_packageroot_directory = matlabshared.supportpkg.getSupportPackageRoot;
source_path = fullfile(Support_packageroot_directory,'toolbox','target','supportpackages','freedomboard','src');
include_path = fullfile(Support_packageroot_directory,'toolbox','target','supportpackages','freedomboard','include') ;

backup_folder=fullfile(Support_packageroot_directory,'toolbox','target','supportpackages','freedomboard');
mkdir(fullfile(backup_folder,'backup'));
movefile((fullfile(source_path,'MW_Camera.cpp')),fullfile(backup_folder,'backup'));
movefile(fullfile(source_path,'MW_DC_Motor.cpp'),fullfile(backup_folder,'backup'));
movefile(fullfile(source_path,'MW_Servo.cpp'),fullfile(backup_folder,'backup'));
movefile(fullfile(include_path,'MW_Camera.h'),fullfile(backup_folder,'backup'));
copyfile ('*.cpp' , source_path)
copyfile ('*.h' , include_path)

disp('Update successful!')
end