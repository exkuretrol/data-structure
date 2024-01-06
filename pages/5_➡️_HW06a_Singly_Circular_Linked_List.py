import streamlit as st
import redirect as rd
from homework import SinglyCircularLinkedList
import random

st.set_page_config(
    page_title="單向循環鏈結串列",
    page_icon="➡️"
)

st.header("單向循環鏈結串列")
st.caption("Singly Circular Linked List")

c1 = st.container(border=True)
c2 = st.container(border=True)

with c1:
    # TODO: add action update
    input_options_action = {'create': '新增', 'delete': '刪除', 'search': '搜尋'}

    input_action = st.radio("action", input_options_action, format_func=lambda x: input_options_action.get(x), horizontal=True)

    input_options_location = {'head': '最前', 'tail': '最後', 'target': '目標', 'before': '目標之前', 'after': '目標之後'}

    if input_action == "create":
        input_options_location.pop("target")
    elif input_action == "search":
        input_options_location = {'target': '目標'}

    input_location = st.radio("location", input_options_location, format_func=lambda x: input_options_location.get(x), horizontal=True, index=1 if input_action=='create' else 0 if input_action=='search' else 2)

with c2:
    if input_action == 'create':
        input_options_method = {'manual': '手動設定', 'random': '隨機產生'}

        col1, col2 = st.columns(2)
        with col1:
            input_method = st.radio('method', input_options_method, format_func=lambda x: input_options_method.get(x), index=1, horizontal=True)
        with col2:
            if input_location in ['target', 'before', 'after']:
                input_target = st.number_input('target', min_value=0, max_value=2**31-1)

        if (input_method == "manual"):
            input_num = st.number_input("num", min_value=0, max_value=2**31-1)
        else:
            col1, col2 = st.columns([1, 3], gap="medium")
            with col1:
                input_n = st.number_input("n", min_value=1, max_value=10000, value=3)
            with col2:
                input_minmax = st.slider("minmax", min_value=0, max_value=1000, value=(0, 100))
            # st.sidebar.markdown('''
            # `n`：要隨機輸入堆疊幾個數字。

            # `minmax`：輸入堆疊的數字的最大最小值。
            # ''')
    else:
        if input_location in ['target', 'before', 'after']:
            input_target = st.number_input('target', min_value=0, max_value=2**31-1)

    col1, col2, col3, _ = st.columns([2, 2, 2, 5])
    with col1:
        btn_action = st.button(input_options_action.get(input_action), type="primary", use_container_width=True)
    with col2:
        btn_empty = st.button(":violet[清空 :bomb:]", type="secondary", use_container_width=True)
    with col3:
        btn_invert = st.button(":rainbow[反轉 ↩]", use_container_width=True)

input_options_detailed = {'detailed': '詳細顯示（包含記憶體位址）', 'normal': '僅顯示串列內容'}
input_detailed = st.radio('output', input_options_detailed, format_func=lambda x: input_options_detailed.get(x), index=1)

@st.cache_resource
def init_list():
    l = SinglyCircularLinkedList()
    return l

l = init_list()

def insert(el: int, target: int = None):
    try:
        match input_location:
            case "head":
                res = l.insert_front(el)
            case "tail":
                res = l.insert_rear(el)
            case "before":
                res = l.insert_before(target, el)
            case "after":
                res = l.insert_after(target, el)
            
        if res == -1: raise ValueError(f"找不到目標數字 {target}")
    except ValueError as e:
        st.toast(e)

def delete(target: int = None):
    try:
        match input_location:
            case "head":
                res = l.delete_front()
            case "tail":
                res = l.delete_rear()
            case "target":
                res = l.delete_node(target)
            case "before":
                res = l.delete_before(target)
            case "after":
                res = l.delete_after(target)

        if res == -1: 
            if input_location in ["head", "tail"]:
                raise ValueError(f"串列已空")
            else:
                raise ValueError(f"找不到目標數字 {target}")
        if res == -2: raise ValueError(f"{input_options_location.get(input_location)}沒有數字")
    except ValueError as e:
        st.toast(e)

def search(target: int):
    try:
        res = l.search_node(target)
        if res == -1: raise ValueError(f"找不到目標數字 {target}")
        else: st.toast("找到了")
    except ValueError as e:
        st.toast(e)

if btn_action:
    match input_action:
        case "create":
            if input_method == "manual":
                if input_location in ["head", "tail"]:
                    insert(el=input_num)
                elif input_location in ["after", "before"]:
                    insert(el=input_num, target=input_target)
            else:
                m, M = input_minmax
                for _ in range(input_n):
                    num = random.randint(m, M)
                    if input_location in ["head", "tail"]:
                        insert(el=num)
                    elif input_location in ["after", "before"]:
                        insert(el=num, target=input_target)
        case "delete":
            if input_location in ["tail", "head"]:
                delete()
            else:
                delete(input_target)
        case "search":
            search(input_target)

if btn_empty:
    l.delete_all_nodes()

if btn_invert:
    l.invert()

code = st.code(language="css", body="", line_numbers=True)

with rd.stdout(to=code):
    detailed = True if input_detailed == "detailed" else False
    if detailed:
        l.print_detailed_nodes()
    else:
        l.print_nodes()
