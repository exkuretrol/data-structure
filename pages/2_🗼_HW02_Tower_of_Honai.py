import streamlit as st
from homework import Honai


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
    honai = Honai(int(input_layer))
    honai.run(int(input_layer))

    ls = honai.getData()
    t = ""
    for i, l in enumerate(ls):
        t = t + ("Step " + str(i + 1) + ": " + l) + "\n"

    st.code(t)
