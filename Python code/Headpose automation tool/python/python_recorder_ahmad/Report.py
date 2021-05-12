import csv
import Logger
import pandas as pd
import matplotlib.pyplot as plt
import os
from sklearn.metrics import mean_absolute_error


def open_file(path):
    return pd.read_csv(path)


def plot(title, x, y_predict, y_gt, final_results_path, y_predict_2=None, add_to_title=None):
    min_shape = min(x.shape[0], y_gt.shape[0], y_predict.shape[0])
    if y_predict_2 is not None:
        min_shape = min(min_shape, y_predict_2.shape[0])
        plt.plot(x[0:min_shape], y_predict_2[0:min_shape], '.-g', label='predicted_with_calibration')
    plt.plot(x[0:min_shape], y_predict[0:min_shape], '.-b', label='predicted')
    plt.plot(x[0:min_shape], y_gt[0:min_shape], '.-r', label='gt')
    plt.legend()
    plt.grid()
    print(f'add_to_title: {add_to_title}')
    ext_title = title + add_to_title
    plt.title(ext_title)
    file_name = title + '.jpeg'
    plt.savefig(os.path.join(final_results_path, file_name))
    plt.clf()
    plt.cla()


def compute_mae_when_valid(gt, pred):
    filtered_gt = gt.dropna(subset=['roll'])
    filtered_pred = pred.dropna(subset=['roll'])
    filtered_gt_idx = filtered_gt['Unnamed: 0']  # +\
    filtered_pred_idx = filtered_pred['Unnamed: 0']
    filtered_idx = pd.Series(list(set(filtered_gt_idx).intersection(set(filtered_pred_idx))))
    filtered_gt_new = gt.iloc[filtered_idx]
    filtered_pred_new = pred.iloc[filtered_idx]
    assert len(filtered_gt_new.index) == len(filtered_pred_new.index)
    np_gt = filtered_gt_new.to_numpy()
    np_pred = filtered_pred_new.to_numpy()
    np_gt = np_gt[1:, 1:4]
    np_pred = np_pred[1:, 1:4]
    mae = mean_absolute_error(np_gt, np_pred, multioutput='raw_values')
    avg_mae = mean_absolute_error(np_gt, np_pred)
    return mae, avg_mae


def make_graph(result_folder, results_csv_path):
    reslts = open_file(results_csv_path)
    #pred = open_file(results_csv_path)
    # mae_pred, avg_pred_mae = compute_mae_when_valid(gt, pred)
    add_to_title = ''  # f'mae w.o calibration -r: {mae_pred[0]:.2f},p: {mae_pred[1]:.2f}, y:{mae_pred[2]:.2f} t: {avg_pred_mae:.2f},\n'
    #print(f'{add_to_title}')
    plot('roll_gt_vs_calib_prediction', reslts.Test_NO, reslts.roll, reslts.GT_roll, result_folder, None,
         add_to_title=add_to_title)
    plot('pitch_gt_vs_calib_prediction', reslts.Test_NO, reslts.pitch, reslts.GT_pitch, result_folder, None,
         add_to_title=add_to_title)
    plot('yaw_gt_vs_calib_prediction', reslts.Test_NO, reslts.yaw, reslts.GT_yaw, result_folder, None,
         add_to_title=add_to_title)


def compare(Freddy_results_path, Algo_results_path, result_folder):
    f1 = open(Freddy_results_path, 'r')
    Freddy_results = csv.reader(f1)
    new_log = Logger.log_utils(result_folder, 'Merged')
    for Freddy_row in Freddy_results:
        f2 = open(Algo_results_path, 'r')
        Algo_results = csv.reader(f2)
        for Algo_row in Algo_results:
            if (Freddy_row[1] == Algo_row[0]):
                new_log.append_log(Freddy_row + Algo_row[1:])

    new_log.writetofile()


def main():
    Freddy_results_path = '/home/ahmad/Results/20200204_194024_results.csv'
    Algo_results_path = '/home/ahmad/Results/hp_results.csv'
    result_folder = '/home/ahmad/Results'

    compare(Freddy_results_path, Algo_results_path, result_folder)
    make_graph(result_folder, result_folder + '/Merged_results.csv')


if __name__ == '__main__':
    main()
