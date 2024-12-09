@echo off
set argu=class/Date.cpp class/Finance.cpp class/Interaction.cpp class/MainApp.cpp class/Payment.cpp class/RentalPost.cpp class/Transaction.cpp class/User.cpp
g++ main.cpp %argu% -I headers -o main