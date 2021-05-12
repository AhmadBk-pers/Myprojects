         import os
import csv


class log_utils:
   def __init__(self, results_folder_path, name):
      self.is_log = False
      self.header = False
      self.folder_path = results_folder_path
      if(self.folder_path != ''):
         self.is_log = True
         self.file_name = str(name)+"_head_results.csv"
         self.file_path = self.folder_path + "/" + self.file_name
         if os.path.exists(self.file_path):
            os.remove(self.file_path)
         self.logs = []

   def append_log(self, log):
      if self.is_log:
         self.logs.append(log)

   def writetofile(self):
      if self.is_log:
         with open(self.file_path, 'w+') as csvFile:
            writer = csv.writer(csvFile)
            writer.writerows(self.logs)
         csvFile.close()



