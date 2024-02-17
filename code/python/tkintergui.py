import tkinter as tk
from tkinter import ttk
import logger_serial as ls
import analyse_csv as acv

filename=''
filepath =''
class MainApp:
    def __init__(self, master):
        self.master = master
        self.master.title("Main Application")
        self.master.geometry("500x400")
        # self.master.configure(background="black")
        self.frame = tk.Frame(self.master, padx=20, pady=30)
        self.frame.pack(padx=40, pady=60)
        # Create a button to open the second app
        self.label = ttk.Label(self.frame, text="Goa College of Engineering")
        self.label.pack(pady=10)
        self.livebutton = ttk.Button(self.frame, text="Live", command=self.open_ai_app)
        self.livebutton.pack(pady=20)
        self.trainbutton = ttk.Button(self.frame, text="Train", command=self.open_second_app)
        self.trainbutton.pack(pady=20)

    def open_second_app(self):
        # Open the second app in a new window
        SecondAppWindow(self.master)

    def open_ai_app(self):
        # Open the second app in a new window
        AIAppWindow(self.master)

class SecondAppWindow(tk.Toplevel):
    def __init__(self, master):
        super().__init__(master)
        self.title("Neural feedback")
        self.geometry("500x400")
        # self.configure(background="black")
        # Create the widgets for the second app
        self.frame2 = tk.Frame(self, padx=20, pady=30)
        self.frame2.pack(padx=40, pady=60)
        label = ttk.Label(self.frame2, text="This is the second app.")
        label.pack(pady=20)
        logdata = ttk.Button(self.frame2, text="Logdata", command=self.logdatafile)
        logdata.pack(pady=20)

        visualise = ttk.Button(self.frame2, text="Visualise", command=self.visualise)
        visualise.pack(pady=20)

    def logdatafile(self):
        global filename, filepath
        filename,filepath = ls.main(0)

    def visualise(self):
        if filename == '' and filepath == '':
            acv.main(0)
        else:
            acv.get_fft(filename,filepath)


class AIAppWindow(tk.Toplevel):
    def __init__(self, master):
        super().__init__(master)
        self.title("AI Application")
        self.geometry("500x400")
        # self.configure(background="black")
        self.frame3 = tk.Frame(self, padx=20, pady=30)
        self.frame3.pack(padx=40, pady=60)
        label = tk.Label(self.frame3, text="This is the AI app.")
        label.pack(pady=20)



if __name__ == "__main__":
    root = tk.Tk()

    # Set the theme
    root.tk.call("source", "azure.tcl")
    root.tk.call("set_theme", "dark")
    # sv_ttk.set_theme("dark")

    app = MainApp(root)

    # Set a minsize for the window, and place it in the middle
    root.update()
    root.minsize(root.winfo_width(), root.winfo_height())
    x_cordinate = int((root.winfo_screenwidth() / 2) - (root.winfo_width() / 2))
    y_cordinate = int((root.winfo_screenheight() / 2) - (root.winfo_height() / 2))
    root.geometry("+{}+{}".format(x_cordinate, y_cordinate-20))
    root.mainloop()
