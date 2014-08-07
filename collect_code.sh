#!/bin/sh

# shopt -s nullglob
# srcfiles=(src/**/*.cpp)
# includefiles=(include/**/*.h)

srcfiles=($(find "src" -name '*.cpp'))
includefiles=($(find "include" -name '*.h'))

result=collected_code.cpp

if [ -f $result ]; then
    rm $result
    touch $result
else
    touch $result
fi

for i in "${includefiles[@]}" "${srcfiles[@]}"; do
    echo >> $result
    echo "/******************************************************" >> $result
    echo "*                                                     *" >> $result
    echo "*    "$i  >> $result
    echo "*                                                     *" >> $result
    echo "******************************************************/" >> $result
    echo >> $result
    cat $i | sed '/^$/d' >> $result
done
