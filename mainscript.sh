#!/bin/bash
echo "-------------------------------Меню---------------------------------------"
echo "Какое приложение вы хотите запустить?"
select proga in C wxmaxima LibreOffice_Calc
do
	case $proga in
		C)
			gcc -o main kursovaya.c
      		./main
      		exit
      		;;
    	wxmaxima)
			echo "Контрольный расчет с заданными значениями или Контрольный расчет со значениями из файла?"
			select maxima in raschet file
			do
				case $maxima in
					raschet)
      					open ~/Documents/kursovaya1/rascheti_maxima.wxmx
      					exit
      					;;
      				file)
						open ~/Documents/kursovaya1/rascheti_file.wxmx
						exit
						;;
					*)
						echo "Введите корректный вариант, $REPLY нет в списке"
						;;
			  esac
      		done
      		;;
      	LibreOffice_Calc)
			echo "Это приложение пока недоступно"
			;;
    	*)
      		echo "Введите корректное приложение, $REPLY приложения нет в списке"
      		;;
  esac
done