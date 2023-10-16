import streamlit as st
from homework import Permutation, Honai

st.set_page_config(
    page_title="08170875 資料結構作業",
    page_icon="😾"
)

st.write("""
# 作業存放區
""")

st.caption("08170875 陳家瑋")

st.sidebar.info("點選一個作業展示")

st.sidebar.markdown('''
<small>[data structure](https://github.com/exkuretrol/data-structure)  | Oct 2023 | [Chiawei Chen](https://www.kuaz.info/)</small>
''', unsafe_allow_html=True)


