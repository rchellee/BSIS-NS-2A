from tkinter import *
from tkinter import Tk, Label
from tkinter import ttk
from tkinter import messagebox
import sqlite3 as sqltor
from time import sleep
from datetime import datetime
import csv

tup_Id = []
no_duplicates = []

conn=sqltor.connect('main.db') #main database
cursor=conn.cursor() #main cursor
cursor.execute("""CREATE TABLE IF NOT EXISTS poll
                    (name)""")


class EVoting:

    def __init__(self):
        # setting root window:
        self.root = Tk()
        self.root.config(bg="black")
        self.root.title("Voting System")
        self.root.attributes("-fullscreen", True)
        self.root.resizable(0,0)
        
        #body UI
        Frame(self.root,width=1500,height=150,bg="gray").place(x=0,y=0)

        Label(self.root, text="E - V O T I N G    \nS Y S T E M", font =('Times New Roman Bold',40),
            bg = "gray", fg="black").place(x=300, y=1)
        Label(self.root, text="made by:", font ="Bahnschrift 12",
            bg = "gray", fg="black").place(x=665, y=9)
        Label(self.root, text="R I T C H E L L E   T .   R U E R A S", font =('Courier',14),
            bg = "gray", fg="black").place(x=665, y=30)
        Label(self.root, text="M O N I Q U E  K Y L E   C A B I G T I N G", font =('Courier',14),
            bg = "gray", fg="black").place(x=665, y=50)
        Label(self.root, text="G W Y N N   C U J A R D O", font =('Courier',14),
            bg = "gray", fg="black").place(x=665, y=70)


        # update root to see animation:
        self.root.update()
        self.play_animation()
        self.menu()
            
        #window in mainloop:
        self.root.mainloop()

    # loader animation:
    def play_animation(self):
        Frame(self.root,width=1500,height=40,bg="black").place(x=0,y=730)
        # loading text:

        Label(self.root, text="Please Wait While Loading...", font ="Bahnschrift 12",
            bg = "black", fg="#FFBD09").place(x=600, y=300)
        # loading blocks:
        for i in range(62):
            Label(self.root, bg="#1F2732", width=2, height=1).place(x=(i+0)*22, y=740)
        for i in range(1):
            for j in range(62):
                # make block yellow:
                Label(self.root, bg="#FFBD09", width=2, height=1).place(x=(j+1)*22, y=740)
                sleep(0.04)
                self.root.update_idletasks()
                # make block dark:
                Label(self.root, bg="#1F2732", width=2, height=1).place(x=(j+1)*22, y=740)
            
    def userLogin(self):#LOG-IN
        def proceed1():
            Account_number =(self.tupID.get())
            check=self.check_voter(Account_number)
            if check == 1:
                messagebox.showinfo('Warning!!','You already voted!!')
                cr.destroy()
            elif check ==0:
                for row in tup_Id:
                    if Account_number in row:
                        found = True
                        voted.append(Account_number)
                        with open('Voted.csv', "a", encoding="utf-8") as f:
                            writer = csv.writer(f)
                            writer.writerows([voted])
                        messagebox.showinfo('Message','Log-In Success!')
                        cr.destroy()
                        self.polls()
                if not found:
                    messagebox.showinfo('Error','Your ID is not registered on the system!!')
                    cr.destroy()  
            else:
                messagebox.showinfo('Error','No Duplication of Votes Allowed!')
                cr.destroy()

        voted=[]
        self.tupID = StringVar()
        cr=Toplevel()
        cr.geometry('400x100')
        cr.title('USER LOG-IN')
        Label(cr,text=' Enter TUP ID: ').place(x=160, y=5)
        my_entry = Entry(cr, font = ("Century Gothic", 12), textvariable = self.tupID )
        my_entry.place(x=100, y=30)
        Button(cr,text='Proceed',command=proceed1).place(x=180, y=70)
               

    def create(self):#CREATE A POLL
        
        def proceed():
            global pcursor
            pname=name.get() #pollname
            can=cname.get()   #candidatename
            if pname=='':
                return messagebox.showerror('Error','Enter poll name')
            elif can=='':
                return messagebox.showerror('Error','Enter candidates')
            else:
                candidates=can.split(',') #candidate list
                command='insert into poll (name) values (?);'
                cursor.execute(command,(pname,))
                conn.commit()
                pd=sqltor.connect(pname+'.db') #poll database
                pcursor=pd.cursor() #poll cursor
                pcursor.execute("""CREATE TABLE IF NOT EXISTS polling
                    (name TEXT,votes INTEGER)""")
                for i in range(len(candidates)):
                    command='insert into polling (name,votes) values (?, ?)'
                    data=(candidates[i],0)
                    pcursor.execute(command,data)
                    pd.commit()
                pd.close()
                messagebox.showinfo('Success!','Poll Created')
                cr.destroy()

        name=StringVar()
        cname=StringVar()
        cr=Toplevel()
        cr.geometry('500x150')
        cr.title('Create New Poll')
        Label(cr,text='Enter Details',font='Helvetica 12 bold').grid(row=1,column=2)
        Label(cr,text=' Enter Poll name: ').grid(row=3,column=1)
        Entry(cr,width=30,textvariable=name).grid(row=3,column=2) #poll name
        Label(cr,text='(eg: captain elections)').place(x=354,y=25)
        Label(cr,text=' Enter Candidates: ').grid(row=5,column=1)
        Entry(cr,width=45,textvariable=cname).grid(row=5,column=2) #candidate name
        Label(cr,text='Note: Enter the candidate names one by one by putting commas').grid(row=6,column=2)
        Label(cr,text='eg: candidate1,candate2,candidate3....').grid(row=7,column=2)
        Button(cr,text='Proceed',command=proceed).grid(row=8,column=2)

    def polls(self): #mypolls
        def proceed():
            global plname
            plname=psel.get()
            if plname=='-SELECT-':
                return messagebox.showerror('Error','select a category')
            else:
                mpolls.destroy()
                self.pollpage()
        cursor.execute('select name from poll')
        data=cursor.fetchall()
        pollnames=['-SELECT-']
        for i in range(len(data)):
            data1=data[i]
            ndata=data1[0]
            pollnames.append(ndata)
        psel=StringVar()
        mpolls=Toplevel()
        mpolls.geometry('300x300')
        mpolls.title('Voting Program')
        Label(mpolls,text='Select a Category',font='Helvetica 12 bold').grid(row=1,column=3)
        select=ttk.Combobox(mpolls,values=pollnames,state='readonly',textvariable=psel)
        select.grid(row=2,column=3)
        select.current(0)
        Button(mpolls,text='Proceed',command=proceed).grid(row=2,column=4)

    def pollpage(self): #page for polling
        def proceed():
            chose=choose.get()
            print(chose)
            command='update polling set votes=votes+1 where name=?'
            pd.execute(command,(chose,))
            pd.commit()
            messagebox.showinfo('Success!','You have voted')
            self.polls()
        choose=StringVar()
        names=[]
        pd=sqltor.connect(plname+'.db') #poll database
        pcursor=pd.cursor() #poll cursor
        pcursor.execute('select name from polling')
        data=pcursor.fetchall()
        for i in range(len(data)):
            data1=data[i]
            ndata=data1[0]
            names.append(ndata)
        print(names)
        ppage=Toplevel()
        ppage.geometry('300x300')
        ppage.title('Poll')


        Label(ppage,text='Vote for ONLY one person!').grid(row=1,column=3)
        for i in range(len(names)):
            Radiobutton(ppage,text=names[i],value=names[i],variable=choose).grid(row=2+i,column=1)
        Button(ppage,text='Vote',command=proceed).grid(row=2+i+1,column=2)

    def selpl(self): #pollresults
        def results():
            sel=sele.get()  #selected option
            if sel=='-SELECT-':
                return messagebox.showerror('Error','Select Poll')
            else:
                pl.destroy()
                def project():
                    names=[]
                    votes=[]
                    for i in range(len(r)):
                        data=r[i]
                        names.append(data[0])
                        votes.append(data[1])
   

                res=Toplevel() #result-page
                res.geometry('300x300')
                res.title('Results!')
                Label(res,text='Voting Result!',font='Helvetica 12 bold').grid(row=1,column=2)
                con=sqltor.connect(sel+'.db')
                pcursor=con.cursor()
                pcursor.execute('select * from polling')
                r=pcursor.fetchall() #data-raw
                for i in range(len(r)):
                    data=r[i]
                    Label(res,text=data[0]+': '+str(data[1])+' votes').grid(row=2+i,column=1)
                Button(res,text='EXIT',command=res.destroy).grid(row=2+i+1,column=2)


        cursor.execute('select name from poll')
        data=cursor.fetchall()
        pollnames=['-select-']
        for i in range(len(data)):
            data1=data[i]
            ndata=data1[0]
            pollnames.append(ndata)
        sele=StringVar()
        pl=Toplevel()
        pl.geometry('300x200')
        pl.title('Voting System')
        Label(pl,text='Select Category to View',font='Helvetica 12 bold').place(x=70, y=5)
        sel=ttk.Combobox(pl,values=pollnames,state='readonly',textvariable=sele)
        sel.place(x=90, y=40)
        sel.current(0)
        Button(pl,text='Get Results',command=results).place(x=130, y=80)

    def check_voter(self, tupm): #to search for a student
            with open('Voted.csv', "r", encoding="utf-8") as f:
                reader = csv.reader(f)
                for row in reader:
                    if len(row) > 0:
                        if tupm == row[0]:
                            print("----- Voter Already Voted -----")
                            return 1
                else:
                    return 0



    def menu(self):
        Label(self.root,text='M A I N    M E N U',font='Courier 30 bold',bg='gray').place(x=460, y=300)
        Button(self.root,text='CREATE NEW POLL',font='Helvetica 15',bg='gray',command=self.create).place(x=600, y=400)
        Button(self.root,text='VOTE',font='Helvetica 15',bg='gray',command=self.userLogin).place(x=670, y=450)
        Button(self.root,text='Poll Results', font='Helvetica 15',bg='gray',command=self.selpl).place(x=645, y=500)
        Button(self.root,text='EXIT',font='Helvetica 8',command=self.root.destroy).place(x=690, y=550)

with open('Accnum.csv','r') as file:
    reader= csv.reader(file)

    for row in reader:
         tup_Id.append(row)



if __name__ == "__main__":
    EVoting()