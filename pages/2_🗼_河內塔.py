import streamlit as st
from homework import Honai


st.set_page_config(
    page_title="河內塔",
    page_icon="🗼"
)

input_layer = st.number_input("層數", step = 1, value=3)
run = st.button("啟動", type="primary")

if run:
    honai = Honai(int(input_layer))
    honai.run(int(input_layer))

    ls = honai.getData()
    for i, l in enumerate(ls):
        st.write(l + f" [{i}]")