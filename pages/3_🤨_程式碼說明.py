import streamlit as st
st.set_page_config(
    page_title="程式碼說明",
    page_icon="🤨",
)

st.header("程式碼說明")

tab0, tab1, tab2, tab3, tab4 = st.tabs(["main.cpp", "permutation.hpp", "tower-of-honai.hpp", "Permutation.py", "Tower_of_Honai.py"])

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

with tab3:
    with open('pages/1_🌧️_HW02_Permutation.py') as f:
        src = f.read()
    st.code(src)

with tab4:
    with open('pages/2_🗼_HW02_Tower_of_Honai.py') as f:
        src = f.read()
    st.code(src)