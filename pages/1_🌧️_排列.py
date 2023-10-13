import streamlit as st
from homework import Permutation

st.set_page_config(
    page_title="排列",
    page_icon="🌧️"
)

input_types_names = ['Numbers', 'String']

input_types = st.radio('輸入變數類型', input_types_names)


if input_types == 'Numbers':
    input_number = st.number_input("輸入數字", step=1, value=3)
else:
    input_text = st.text_input("輸入字串", value="你好啊旅行者")


run = st.button("啟動", type="primary")

if run:
    ls = [];
    if input_types == 'Numbers':
        perm = Permutation(input_number)

    else:
        perm = Permutation(input_text)
    perm.run(0)
    ls = perm.getData()

    for i, l in enumerate(ls):
        st.write(l + f" [{i}]")