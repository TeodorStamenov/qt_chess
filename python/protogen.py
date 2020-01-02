import os
import subprocess

def main():
    src="../protofiles";
    cpp_out="../cpp/source/protomessages"
    js_out="../javascript/proto_messages"
    protofiles = os.listdir(src)

    for proto in protofiles:    
        protofile = src + "/" + proto
        subprocess.Popen("./protoc.exe "\
                        "--proto_path={0} "\
                        "--cpp_out={1} "\
                        "{2}".format(src, cpp_out, protofile))
        subprocess.Popen("./protoc.exe "\
                        "--proto_path={0} "\
                        "--js_out=import_style=commonjs,binary:{1} "\
                        "{2}".format(src, js_out, protofile))                        
    
main()