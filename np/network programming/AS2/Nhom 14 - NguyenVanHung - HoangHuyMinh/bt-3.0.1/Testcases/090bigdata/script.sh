# test large data files
../../bigt -n 60000
../../bigtdel -n 60000
../../bt <<EOF
o test_db
f
lko
q
EOF
