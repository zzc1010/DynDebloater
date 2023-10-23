/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "art_field.h"

#include "art_field-inl.h"
#include "base/utils.h"
#include "class_linker-inl.h"
#include "dex/descriptors_names.h"
#include "gc/accounting/card_table-inl.h"
#include "handle_scope.h"
#include "mirror/class-inl.h"
#include "mirror/object-inl.h"
#include "mirror/object_array-inl.h"
#include "runtime.h"
#include "scoped_thread_state_change-inl.h"
#include "well_known_classes.h"
#include "thread.h"
#include "thread_list.h"
#include "utils/Log.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
// #include <runtime_globals.h>

namespace art {

// static std::string MINIMA_file_path = "/data/data/edu.smu.minimaconfig/files/schema/mySchema.txt";

// static std::string hook_method_name = "void edu.smu.minimaconfig.SettingsActivity.empty_Hook()";

// static std::vector<std::string> target_method_string_vector = {};

//"void de.drmaxnix.birthdaycountdown.MainActivity.birthdate_picker_open(int, int, int)", 
// void MY_getFiles(){
// 	long   hFile   =   0;

// 	struct _finddata_t fileinfo;
// 	string p;
// 	if((hFile = _findfirst(p.assign(path).append("/*").c_str(),&fileinfo)) !=  -1)
// 	{
// 		do
// 		{
// 			if((fileinfo.attrib &  _A_SUBDIR))
// 			{
// 				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
// 					getFiles( p.assign(path).append("/").append(fileinfo.name), files );
// 			}
// 			else
// 			{
// 				files.push_back(p.assign(path).append("/").append(fileinfo.name) );
// 			}
// 		}while(_findnext(hFile, &fileinfo)  == 0);
// 		_findclose(hFile);
// 	}

// }


// void* RunMonitoringThread() {
//   Runtime* runtime = Runtime::Current();
//   CHECK(runtime->AttachCurrentThread("Start Schema Monitoring",true, runtime->GetSystemThreadGroup(),!runtime->IsAotCompiler()));
// }

// void MYadd_target_vector(std::string methodString){
//   target_method_string_vector.push_back(methodString);
// }

// bool MYmatch_hook_method(std::string methodString){
//     if (methodString.compare(hook_method_name) == 0) {
//         ALOGI("Match hook method!");
//         return true;
//     }
//     return false;
// }

// bool MYmatch_target_method(std::string s){
//     // if(MYis_target_vector_empty())
//       // MYadd_target_vector("void de.drmaxnix.birthdaycountdown.MainActivity.birthdate_picker_open(int, int, int)");
//     // ALOGI("Current vector address: %p", &target_method_string_vector);
//     ALOGI("Current vector size: %d", (int)target_method_string_vector.size());
//     // for(unsigned int i=0;i<target_method_string_vector.size();i++){
//     //     ALOGI("%s", target_method_string_vector[i].c_str());
//     // }
//     for (auto str : target_method_string_vector) {
//           if (str.compare(s) == 0) {
//             ALOGI("Match target method!");
//             return true;
//           }
//     }
//     return false;
// } 

// void MYmake_file(std::string fileName){
//   ALOGI("Start to add a file at %s", fileName.c_str());
//   std::ofstream fout(fileName.c_str());
//   if(!OS::FileExists(fileName.c_str())){
//     ALOGI("File does not exist at %s, create it.", fileName.c_str());
//     if (fout) { 
//       fout <<"test this message"<< std::endl; 
//       fout.close(); 
//     }
//   }else{
//     ALOGI("File exists at %s, create it.", fileName.c_str());
//   }
// }


// std::vector<std::string> MYreadFile(){
//   // std::string file_name = "/mnt/sdcard/mySchema.txt";
//   // fin.open(, std::iso::in);
//   std::vector<std::string> _method_string_vector = {};
//   if(!target_method_string_vector.empty()){
//     _method_string_vector = target_method_string_vector;
//   }
//   ALOGI("Start looking for %s",MINIMA_file_path.c_str());
//   std::ifstream fin;
//   fin.open(MINIMA_file_path.data());
//   // if(OS::FileExists(MINIMA_file_path.c_str())){
//   if(fin){
//       ALOGI("File Exists%s",MINIMA_file_path.c_str());
//       // std::ifstream fin(MINIMA_file_path);
//       // if(fin){
//         // _method_string_vector = {};
//         std::string line;
//         while(getline(fin, line)){
//           line.erase(line.find_last_not_of(' ')+1, std::string::npos);
//           line.erase(0, line.find_first_not_of(' '));
//          _method_string_vector.push_back(line);
//         }
//       // }
//       for(unsigned int i=0;i<_method_string_vector.size();i++){
//         ALOGI("%s", _method_string_vector[i].c_str());
//       }
//   }else{
//     ALOGI("File Not Exist:%s",MINIMA_file_path.c_str());
//   }
//   return _method_string_vector;
// }

// bool MYis_target_vector_empty(){
//   return target_method_string_vector.empty(); 
// }

// void MY_print_all_files_in_root(std::string file_path){
//   ALOGI("start to print out files1: %s", file_path.c_str());
//   DIR *dir;
//   if ( (dir=opendir(file_path.c_str())) == 0 ){
//     ALOGI("open dir failed");
//     return;
//   }
//   struct dirent *stdinfo;
//   ALOGI("start to print out files: %s", file_path.c_str());
//   while ((stdinfo=readdir(dir)))
//   {
//         switch(stdinfo->d_type) {
//                 case DT_DIR:
//                         ALOGI("DIR        %s\n", stdinfo->d_name); 
//                         break;
//                 case DT_REG:
//                         ALOGI("REGFILE    %s\n", stdinfo->d_name); 
//                         break;
//                 default:
//                         //man readdir
//                         break;
//         }
//   }
//   closedir(dir);   
// }

void ArtField::SetOffset(MemberOffset num_bytes) {
  DCHECK(GetDeclaringClass()->IsLoaded() || GetDeclaringClass()->IsErroneous());
  DCHECK_ALIGNED_PARAM(num_bytes.Uint32Value(),
                       Primitive::ComponentSize(GetTypeAsPrimitiveType()));
  // Not called within a transaction.
  offset_ = num_bytes.Uint32Value();
}

ObjPtr<mirror::Class> ArtField::ProxyFindSystemClass(const char* descriptor) {
  DCHECK(IsProxyField());
  ObjPtr<mirror::Class> klass = Runtime::Current()->GetClassLinker()->LookupClass(
      Thread::Current(), descriptor, /* class_loader= */ nullptr);
  DCHECK(klass != nullptr);
  return klass;
}

std::string ArtField::PrettyField(ArtField* f, bool with_type) {
  if (f == nullptr) {
    return "null";
  }
  return f->PrettyField(with_type);
}

std::string ArtField::PrettyField(bool with_type) {
  std::string result;
  if (with_type) {
    result += PrettyDescriptor(GetTypeDescriptor());
    result += ' ';
  }
  std::string temp;
  result += PrettyDescriptor(GetDeclaringClass()->GetDescriptor(&temp));
  result += '.';
  result += GetName();
  return result;
}

}  // namespace art
