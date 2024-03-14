from os import remove
from random import choice
from string import ascii_uppercase, digits

import streamlit as st
from homework import Permutation
from rcviz import callgraph, viz

from menu import menu_with_redirect

menu_with_redirect()


def recur_vis(text: str, start: int):
    return filename


st.header("排列")
st.caption("Permutation")

st.sidebar.markdown(
    """
`n`：字典序長度，如輸入 3 會以字串 ABC 排列。

`k`：從何處開始排列，0 起算。
"""
)

input_types_names = {"Numbers": "字典序長度", "String": "文字"}

input_types = st.radio(
    "輸入排列字串類型",
    input_types_names,
    format_func=lambda x: input_types_names.get(x),
)

if input_types == "Numbers":
    input_number = st.number_input("n", step=1, value=3)
    input_from = st.number_input("k", min_value=0, max_value=input_number - 1, value=0)
else:
    input_text = st.text_input("String", value="原神，啟動")
    input_from = st.number_input(
        "k", min_value=0, max_value=len(input_text) - 1, value=0
    )

verbose = st.checkbox("逐步顯示", value=False)

run = st.button("啟動", type="primary")


if run:
    ls = []
    if input_types == "Numbers":
        perm = Permutation(input_number)
    else:
        perm = Permutation(input_text)
    if verbose:
        perm.toggleTrace()
    perm.run(input_from)
    ls = perm.getData()

    t = ""
    for l in ls:
        t = t + (l) + "\n"

    text = None
    try:
        input_text
    except NameError:
        text = "".join([ascii_uppercase[i] for i in range(input_number)])
    else:
        text = input_text

    callgraph.reset()
    n = len(text)
    ls = list(text)
    ps = list()
    record = ""

    @viz
    def perm(k: int):
        global record, ls, ps
        if k == n - 1:
            perm.track(swap=record)
            return ls
        else:
            for i in range(k, n):
                record = f" ({k}, {i})"
                ps = ls
                ls[k], ls[i] = ls[i], ls[k]
                perm(k + 1)
                ls[k], ls[i] = ls[i], ls[k]
                perm.track(pvs=ps)
        return 0

    perm(input_from)
    filename = "".join(choice(ascii_uppercase + digits) for i in range(10)) + ".svg"
    callgraph.render(filename)

    tab1, tab2 = st.tabs(["逐步排列", "遞迴視覺化"])

    with tab1:
        st.code(t)
    with tab2:
        st.image(filename)
    remove(filename)
