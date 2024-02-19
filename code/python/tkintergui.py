import tkinter as tk
from tkinter import ttk
import logger_serial as ls
import analyse_csv as acv
import sv_ttk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
import numpy as np

filename=''
filepath =''
class MainApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Main Application")
        self.master.geometry("500x400")

        # Create the widgets for the second app
        self.notebook = ttk.Notebook(self.master)
        self.notebook.pack(fill=tk.BOTH, expand=True)

        # Create tabs with frames and widgets
        self.tab1 = ttk.Frame(self.notebook)
        self.tab2 = ttk.Frame(self.notebook)

        self.notebook.add(self.tab1, text="Live")
        self.notebook.add(self.tab2, text="Train")

        # self.frame2 = tk.Frame(self, padx=20, pady=30)
        # self.frame2.pack(padx=40, pady=60)

        self.notebook1 = ttk.Notebook(self.tab2)
        self.notebook1.pack(fill=tk.BOTH, expand=True)

        # Create tabs with frames and widgets
        self.tab3 = ttk.Frame(self.notebook1)
        self.tab4 = ttk.Frame(self.notebook1)
        # self.tab3 = ttk.Frame(self.tab2)
        # self.tab4 = ttk.Frame(self.tab2)

        self.notebook1.add(self.tab3, text="logdata")
        self.notebook1.add(self.tab4, text="Visualise")

        label2 = ttk.Label(self.tab3, text="Ensure that you have connected the device to comport7")
        label2.pack(pady=20)
        label3 = ttk.Label(self.tab4, text="visualise")
        label3.pack(pady=20)
        label1 = ttk.Label(self.tab1, text="This is the ai app.")
        label1.pack(pady=20)
        actual = ttk.Button(self.tab3, text="Actual data", command=self.actual)
        actual.pack(pady=20)

        imaginary = ttk.Button(self.tab3, text="Imaginary data", command=self.visualise)
        imaginary.pack(pady=20)

# class Redirect():

#     def __init__(self, widget):
#         self.widget = widget

#     def write(self, text):
#         self.widget.insert('end', text)
    
    def actual(self):
        global filename, filepath
        filename, filepath = ls.logger_data()
        

    
    def visualise(self):
        global filename, filepath
        filename, filepath = ls.logger_data_img()
        # if filename == '' and filepath == '':
        #     acv.main(0)
        #
        # else:
        #     # Plot the data
        #     # figure1,figure2,figure3 = acv.get_fft(filename,filepath)
        #     fig1 = acv.figure_option_eeg(filename, filepath)
        #     top_level = tk.Toplevel(self.master)
        #     top_level.title("Matplotlib Plot in Tkinter")
        #
        #     canvas = FigureCanvasTkAgg(fig1, master=top_level)
        #     canvas.draw()
        #     canvas_widget = canvas.get_tk_widget()
        #     canvas_widget.pack(fill=tk.BOTH, expand=True)
        #     plt.show()



#
#         self.notebook.add(self.tab1, text="Tab 1")
#         self.notebook.add(self.tab2, text="Tab 2")
#
#         # self.frame2 = tk.Frame(self, padx=20, pady=30)
#         # self.frame2.pack(padx=40, pady=60)
#         label = ttk.Label(self.tab1, text="This is the second app.")
#         label.pack(pady=20)
#         logdata = ttk.Button(self.tab1, text="Logdata", command=self.logdatafile)
#         logdata.pack(pady=20)
#
#         visualise = ttk.Button(self.tab1, text="Visualise", command=self.visualise)
#         visualise.pack(pady=20)



if __name__ == "__main__":
    root = tk.Tk()

    # Set the theme
    # root.tk.call('source', 'azure.tcl')
    # root.tk.call("set_theme", "dark")
    sv_ttk.set_theme("dark")


    app = MainApp(root)

    # # Set a minsize for the window, and place it in the middle
    # root.update()
    # root.minsize(root.winfo_width(), root.winfo_height())
    # x_cordinate = int((root.winfo_screenwidth() / 2) - (root.winfo_width() / 2))
    # y_cordinate = int((root.winfo_screenheight() / 2) - (root.winfo_height() / 2))
    # root.geometry("+{}+{}".format(x_cordinate, y_cordinate-20))
    
    root.mainloop()
