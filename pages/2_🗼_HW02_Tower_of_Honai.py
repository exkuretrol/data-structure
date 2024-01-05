import streamlit as st
from homework import Honai
from rcviz import callgraph, viz
from random import choice
from string import digits, ascii_uppercase
from os import remove


st.set_page_config(
    page_title="河內塔",
    page_icon="🗼"
)

st.header("河內塔")
st.caption("Tower of Honai")

st.sidebar.markdown('''
`n`：河內塔圓盤數，如輸入 3 為三層河內塔。

''')

input_layer = st.number_input(
    "n", step=1, value=3, min_value=1, max_value=10, placeholder="圓盤數")
run = st.button("啟動", type="primary")


if run:
    honai = Honai()
    honai.run(int(input_layer))

    ls = honai.getData()
    t = ""
    for i, l in enumerate(ls):
        t = t + ("Step " + str(i + 1) + ": " + l) + "\n"

    callgraph.reset()
    steps = 0

    @viz
    def honai(n: int, A: chr = 'A', B: chr = 'B', C: chr = 'C'):
        global steps
        if (n == 0):
            return "stop"
        honai(n - 1, A, C, B)
        step = f" disk {n} from {A} to {C} [{steps}]"
        honai.track(step=step)
        steps += 1
        honai(n - 1, B, A, C)

    honai(input_layer)
    filename = ''.join(choice(ascii_uppercase + digits) for i in range(10)) + ".svg"
    callgraph.render(filename)

    tab1, tab2 = st.tabs(["逐步河內塔", "遞迴視覺化"])

    with tab1:
        st.code(t)
    with tab2:
        st.image(filename)
    remove(filename)

