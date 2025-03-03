# pour compiler en .exe :
# pyinstaller --onefile interface.py


import os.path
import sys
import random
import time

from PySide6 import QtCore
from PySide6.QtWidgets import (
    QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, QPushButton, QLabel,
    QLineEdit, QFileDialog
)
from PySide6.QtCore import QTimer
from matplotlib.backends.backend_qt5agg import (
    FigureCanvasQTAgg as FigureCanvas,
    NavigationToolbar2QT as NavigationToolbar,
)
import matplotlib.pyplot as plt

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.spo2 = 80
        self.bpm = 100

        self.datafilename = 'data.txt'
        self.verroudatafilename = '.verrouData'
        self.refresh_rate = 0.25

        self.setWindowTitle("Interface PySide6 avec Matplotlib")

        # Widget principal
        main_widget = QWidget()
        self.setCentralWidget(main_widget)

        # Layout principal
        main_layout = QHBoxLayout(main_widget)

        # Panel gauche
        left_panel = QVBoxLayout()

        # Bouton Start
        self.start_button = QPushButton("Start")
        self.start_button.clicked.connect(self.start_animation)
        left_panel.addWidget(self.start_button)

        self.label_spO2_title = QLabel("SPO2")
        self.label_spO2_title.setStyleSheet("font-weight: bold;")
        self.label_spO2_title.setAlignment(QtCore.Qt.AlignCenter)
        self.label_spO2_title.setFixedHeight(15)
        left_panel.addWidget(self.label_spO2_title)

        # Labels avec police 48
        self.label1 = QLabel("100")
        self.label1.setStyleSheet("font-size: 48px; color : blue;")
        self.label1.setAlignment(QtCore.Qt.AlignCenter)
        left_panel.addWidget(self.label1)

        self.label_bpm_title = QLabel("BPM")
        self.label_bpm_title.setStyleSheet("font-weight: bold;")
        self.label_bpm_title.setAlignment(QtCore.Qt.AlignCenter)
        self.label_bpm_title.setFixedHeight(15)
        left_panel.addWidget(self.label_bpm_title)

        self.label2 = QLabel("80")
        self.label2.setStyleSheet("font-size: 48px; color : orange;")
        self.label2.setAlignment(QtCore.Qt.AlignCenter)
        left_panel.addWidget(self.label2)

        self.label_refresh_title = QLabel("refresh rate")
        self.label_refresh_title.setStyleSheet("font-weight: bold;")
        self.label_refresh_title.setFixedHeight(15)
        left_panel.addWidget(self.label_refresh_title)

        # Champ texte pour le refresh rate
        self.refresh_rate_line = QLineEdit()
        self.refresh_rate_line.setText(str(self.refresh_rate))
        left_panel.addWidget(self.refresh_rate_line)

        self.label_file = QLabel("Data file")
        self.label_file.setStyleSheet("font-weight: bold;")
        self.label_file.setFixedHeight(15)
        left_panel.addWidget(self.label_file)


        # Champ texte pour le fichier sélectionné
        self.file_input = QLineEdit()
        self.file_input.setText(self.datafilename)
        if not (os.path.exists(self.datafilename)):
            self.file_input.setStyleSheet("color : red;")
        left_panel.addWidget(self.file_input)

        # Bouton de sélection de fichier
        self.file_selector_button = QPushButton("Select File")
        self.file_selector_button.clicked.connect(self.select_file)
        left_panel.addWidget(self.file_selector_button)

        # Ajout du panel gauche au layout principal
        main_layout.addLayout(left_panel)

        # Panel droit avec le graphique
        self.figure, self.ax = plt.subplots()
        self.canvas = FigureCanvas(self.figure)
        self.toolbar = NavigationToolbar(self.canvas, self)

        right_panel = QVBoxLayout()
        right_panel.addWidget(self.toolbar)
        right_panel.addWidget(self.canvas)
        main_layout.addLayout(right_panel)

        # Configuration de l'animation
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_plot)

        # Données initiales
        self.x_data = list(range(100))
        self.y1_data = [100 for _ in range(100)]
        self.y2_data = [80 for _ in range(100)]

        # Initialisation des courbes
        self.line1, = self.ax.plot(self.x_data, self.y1_data, label="SPO2")
        self.line2, = self.ax.plot(self.x_data, self.y2_data, label="BPM")

        self.ax.legend()
        self.ax.set_ylim(70, 130)

    def start_animation(self):
        if self.timer.isActive():
            self.timer.stop()
            self.start_button.setText("Start")
        else:
            self.timer.start(100)
            self.start_button.setText("Stop")

    def update_plot(self):
        spo2, bpm = self.readdatafile()

        # Mise à jour des données
        self.y1_data = self.y1_data[1:] + [spo2]
        self.y2_data = self.y2_data[1:] + [bpm]

        # Mise à jour des labels
        self.label1.setText(str(self.y1_data[-1]))
        self.label2.setText(str(self.y2_data[-1]))

        # Mise à jour des courbes
        self.line1.set_ydata(self.y1_data)
        self.line2.set_ydata(self.y2_data)
        self.canvas.draw()

        time.sleep(self.refresh_rate)

    def select_file(self):
        file_name, _ = QFileDialog.getOpenFileName(self, "Select a File")
        if file_name:
            self.file_input.setText(file_name)
            self.datafilename = file_name
            self.file_input.setStyleSheet("color : black;")

    def readdatafile(self):

        if not (os.path.exists(self.verroudatafilename)):
            try:
                v = open(self.verroudatafilename, 'x')
            except IOError:
                print('.', end='')
            else :
                try:
                    f = open(self.datafilename, "r")
                except IOError:
                    print('.', end='')
                else:
                    arrtxt = f.read().split('\n')
                    if len(arrtxt) >= 2:
                        spo2read = arrtxt[0]
                        bpmread = arrtxt[1]
                        if spo2read.isnumeric() and bpmread.isnumeric() :
                            self.spo2 = int(spo2read)
                            self.bpm = int(bpmread)
                        else:
                            print(spo2read)
                            print(bpmread)

                    f.close()
                v.close()
            if(os.path.exists(self.verroudatafilename)):
                try :
                    os.remove(self.verroudatafilename)
                except IOError:
                    print('interface : cannot remove verrouData')


        return self.spo2, self.bpm

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())