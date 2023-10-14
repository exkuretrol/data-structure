import streamlit as st
st.set_page_config(
    page_title="程式碼說明",
    page_icon="🤨",
)

st.header("程式碼說明")

tab0, tab1, tab2 = st.tabs(["main.cpp", "permutation.hpp", "tower-of-honai.hpp"])

with tab0:
    with open('src/main.cpp') as f:
        src = f.read()
    st.code(src, language="cpp")

with tab1:
    with open('src/permutation.hpp') as f:
        src = f.read()
    st.code(src, language="cpp")

with tab2:
    with open('src/tower-of-honai.hpp') as f:
        src = f.read()
    st.code(src, language="cpp")

