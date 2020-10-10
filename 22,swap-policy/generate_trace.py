from subprocess import run, PIPE


def generate_trace():
    from subprocess import Popen, PIPE
    pipe = Popen("valgrind --tool=lackey --trace-mem=yes ls",shell=True ,stdout=PIPE)
    text = pipe.communicate()[0]
    print(text)
 

if __name__ == "__main__":
    generate_trace()
