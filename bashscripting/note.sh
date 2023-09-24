#!/bin/bash


config_file_directory="$HOME"
config_file_name=".note.conf"
config_file_full_path=$config_file_directory/$config_file_name


create_notes_dir () {
        dir=$1
        if ! test -d $dir; then
                echo "directory not found, creating it..."
                mkdir $dir
        fi

}


create_config_file () {

	#echo "The Script needs to create a configuration file under /etc to save needed configurations"
	#echo "This requires root previlege, please provide your password if asked to..."
	touch $config_file_full_path
	echo "type the full path of the directory which you want to keep your notes in:"
	read notes_dir
	create_notes_dir $notes_dir
	echo "notes_directory="$notes_dir >> $config_file_full_path
	echo "last_day=$(date +%F)" >> $config_file_full_path
	chmod +x $config_file_full_path
}


if [[ $1 == "--help" ]]; then
	echo "usage:"
	echo 'note "note 1" "note 2" ...'
	exit 0;
fi





#checking if the configuration file exists
if ! test -e $config_file_full_path; then
	create_config_file
fi



source $config_file_full_path

#checking for the notes directory (in case of manual update of the config file)

if ! test -d $notes_directory; then
	create_notes_dir $notes_directory
fi




today="$(date +%F)"
unix_today="$(date -d $today +%s)"

unix_last_day="$(date -d $last_day +%s)"

if ! [ $unix_today -eq $unix_last_day ]; then	
	echo creating a new note file for today...
	sed -i "s#last_day=$last_day#last_day=$today#" "$config_file_full_path"
	source $config_file_full_path

fi

for note in "$@"; do
	echo "$(whoami) at $today $(date +%H:%M)
		$note" >> $notes_directory/$last_day.note;
done
