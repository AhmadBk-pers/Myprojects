import Freddy
import Logger
import time
import pandas as pd
import datetime
import Report
from pathlib import Path

def perform_test(test_plan_path,results_folder_path):
    count = 0
    test_plan = pd.read_csv(test_plan_path)
    test_name = test_plan.Test_name[0]
    test = Logger.log_utils(results_folder_path, test_name)
    test.append_log(['Test_NO', 'Time', 'GT_roll', 'GT_pitch', 'GT_yaw'])
    while True:
        try:
            test_no = test_plan.Test_NO
            roll = test_plan.roll[count]
            pitch = test_plan.pitch[count]
            yaw = test_plan.yaw[count]
            delay = test_plan.sleep[count]
            Freddy.setPosition("Roll", roll)
            Freddy.setPosition("Pitch", pitch)
            Freddy.setPosition("Yaw", yaw)
            time.sleep(delay)
            yaw, pitch, roll, staus = Freddy.getHeadPosition()
            log = [test_no, datetime.datetime.now().strftime("%Y%m%d_%H%M%S"), str(roll), str(pitch), str(yaw)]
            test.append_log(log)
            count += 1
        except:
            break
    test.writetofile()


def main():
    test_plan_path = '~/Test_plan/test_plan.csv'
    # results_folder_path = '~/Results'

    home = str(Path.home())
    print(home)
    results_folder_path = home + '/Results'
    Freddy_results_path = '/home/ahmad/Results/20200204_194024_results.csv'
    Algo_results_path = '/home/ahmad/Results/hp_results.csv'
    perform_test(test_plan_path, results_folder_path)

    Report.compare(Freddy_results_path, Algo_results_path, results_folder_path)
    Report.make_graph(results_folder_path, results_folder_path + '/Merged_results.csv')


if __name__ == '__main__':
    #main()
    Freddy.resetHeadPosition()
    time.sleep(1)
    print(Freddy.setPosition("Yaw", 90))
    print(Freddy.setPosition("Pitch", 90))
    tempsleep = 0.25
    time.sleep (tempsleep)
    Yaw , pitch, roll, status = Freddy.getHeadPosition()
    print(Yaw , pitch, roll, status)
    time.sleep(tempsleep)
    Yaw, pitch, roll, status = Freddy.getHeadPosition()
    print(Yaw, pitch, roll, status)

